# 单例模式知识点汇总

单例模式（Singleton Pattern）是一种创建型设计模式，核心目标是确保**一个类在整个程序生命周期中仅存在一个实例**，并提供一个全局唯一的访问点，避免频繁创建销毁对象带来的资源开销，同时保证实例的全局可访问性。


## 一、核心实现方式：局部静态变量懒汉式（推荐）
该实现方式是 C++11 及以上标准中最简洁、安全的单例实现之一，兼具懒加载（Lazy Initialization）和线程安全特性。

### 1. 实现核心步骤
- **私有化构造相关函数**：杜绝外部通过构造、拷贝、赋值创建新实例，确保实例唯一性。
  - 私有化默认构造函数：防止外部直接 `new Singleton()` 创建对象。
  - 删除拷贝构造函数：防止外部通过拷贝（如 `Singleton s = Singleton::getInstance()`）创建新实例。
  - 删除复制赋值运算符：防止外部通过赋值（如 `Singleton s1; s1 = Singleton::getInstance()`）创建新实例。
- **提供全局访问点**：通过静态成员函数 `getInstance()` 控制实例的创建与访问，内部使用**局部静态变量**存储唯一实例，确保仅初始化一次。

### 2. 代码实现
```cpp
class Singleton {
private:
    // 1. 私有化默认构造函数（允许类内初始化，此处使用默认实现）
    Singleton() = default;

    // 2. 删除拷贝构造函数（禁止外部拷贝实例）
    Singleton(const Singleton& other) = delete;

    // 3. 删除复制赋值运算符（禁止外部赋值实例）
    Singleton& operator=(const Singleton& other) = delete;

    // （可选）C++11 及以上可删除移动构造和移动赋值，进一步杜绝转移实例
    Singleton(Singleton&& other) = delete;
    Singleton& operator=(Singleton&& other) = delete;

public:
    // 4. 全局访问点：返回类的唯一实例（局部静态变量确保仅初始化一次）
    static Singleton& getInstance() {
        // 局部静态变量特性：首次调用 getInstance() 时初始化，后续调用直接返回已存在的实例
        static Singleton instance;
        return instance;
    }

    // ------------------------------
    // （示例）类的其他成员函数（非核心）
    // ------------------------------
    void doSomething() {
        std::cout << "Singleton instance is working." << std::endl;
    }
};
```

### 3. 调用方式
```cpp
// 全局唯一访问方式：通过静态函数获取实例，无需手动创建
Singleton& instance = Singleton::getInstance();
instance.doSomething(); // 调用实例的成员函数
```


## 二、关键注意事项
### 1. 静态成员变量的初始化规则
若采用「返回指针」而非「返回引用」的实现方式（如传统懒汉式），需在**类内声明静态成员指针**，并在**类外全局作用域初始化**（避免未初始化的野指针问题）。

示例（返回指针的传统实现，需额外注意线程安全）：
```cpp
class Singleton {
private:
    // 类内声明静态成员指针（存储实例地址）
    static Singleton* instance;

    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        // 注意：此代码在 C++11 前非线程安全（需手动加锁）
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

// 类外初始化静态成员指针（必须！否则链接时会报错）
Singleton* Singleton::instance = nullptr;
```

### 2. 静态成员函数的访问规则
- 静态成员函数（如 `getInstance()`）**不属于任何类实例**，没有 `this` 指针，因此默认只能访问「静态成员变量/函数」。
- 若需在静态函数中操作「非静态成员」，需显式传入类实例（如通过 `getInstance()` 获取实例后调用非静态成员）。


## 三、线程安全深度解析
单例模式的线程安全核心在于**避免多线程同时初始化实例导致的「重复创建」问题**，不同实现方式的线程安全性差异较大，需结合 C++ 标准版本判断。

### 1. 局部静态变量懒汉式（本文核心实现）
- **C++11 及以上**：**线程安全**。  
  C++11 标准明确规定：「局部静态变量的初始化会在首次访问时进行，且编译器会自动插入同步锁（如 `std::mutex`），确保即使多线程同时调用 `getInstance()`，也只会初始化一次实例」。
- **C++11 以下**：**非线程安全**。  
  旧标准未规定局部静态变量的初始化同步机制，多线程同时进入 `getInstance()` 可能触发多次 `instance` 初始化，导致内存泄漏或实例不唯一。

### 2. 其他实现方式的线程安全性
| 实现方式       | 核心逻辑                                  | 线程安全性（C++11+） | 优缺点                                  |
|----------------|-------------------------------------------|----------------------|-----------------------------------------|
| 饿汉式（指针） | 程序启动时初始化静态指针（`static Singleton* instance = new Singleton();`） | 安全                 | 优点：无需锁，效率高；缺点：提前占用内存，无法懒加载 |
| 传统懒汉式（指针） | 首次调用时判断 `instance == nullptr` 后初始化 | 非安全（需手动加锁） | 优点：懒加载；缺点：需手动实现锁机制，易出现死锁或性能问题 |

#### 传统懒汉式的线程安全优化（手动加锁）
若需在 C++11 以下环境使用懒汉式，需通过互斥锁（`std::mutex`）保证初始化唯一：
```cpp
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx; // 互斥锁，保护实例初始化

    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        // 双重检查锁定（Double-Checked Locking）：减少锁竞争开销
        if (instance == nullptr) { // 第一次检查：无锁，快速判断是否已初始化
            std::lock_guard<std::mutex> lock(mtx); // 加锁
            if (instance == nullptr) { // 第二次检查：防止多线程等待锁后重复初始化
                instance = new Singleton();
            }
        }
        return instance;
    }
};

// 类外初始化静态成员
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;
```

### 3. 注意：实例创建安全 ≠ 成员访问安全
即使实例的创建过程是线程安全的，**多线程对实例的「非静态成员变量/函数」的并发操作仍可能引发数据竞争**（如多个线程同时调用 `instance->modifyData()` 修改同一成员变量）。

解决方案：
- 对非静态成员的读写操作加锁（如 `std::mutex`）。
- 使用线程安全的数据结构（如 `std::atomic` 修饰成员变量）。