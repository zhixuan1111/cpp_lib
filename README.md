# 说明
根据简历中提到的知识点自己实现一番，并且将**相应的知识点**和**常见面试问题**进行总结。主要分为八个部分，算法、容器、C++新特性、设计模式、并发组件、计算机网络、数据库、常用开发工具命令。最后总结成一个综合性的文档，用于面试辅助。
# 一、算法
## 1.1 查找算法：
- 二分查找：✅
- 线性查找：✅
## 1.2 排序算法
- 冒泡排序：✅
- 快速排序：✅
- 归并排序：✅
- 堆排序
## 1.3 二叉树
# 二、容器
## 2.1 vector：✅
### 2.1.1 vector实现方式
1. vector是一个函数模板类，内部由`T* data`，`size_t capacity`，`size_t size`组成，三个参数的含义分别是：
    - `data`：管理`T`类型的一块内存地址，大小为`capacity`；
    - `size`：当前数组中存放的元素个数。
2. 构造函数实现
    - `vector()`：默认构造函数。构造一个空的 vector，不包含任何元素。
    - `vector(size_t size)`：指定大小的构造函数。构造一个包含 n 个元素的 vector，每个元素使用默认值初始化（对于基本类型通常是 0）。
    - `vector(size_t size,T value)`：指定大小和初始值的构造函数。构造一个包含 n 个元素的 vector，每个元素都被初始化为指定值 value。
    - 还有迭代器范围构造函数、拷贝构造函数、移动构造函数（C++11 起）、初始化列表构造函数、分配器构造函数
### 2.1.2 vector相关面试问题
1. `vector`的扩容机制是什么？
    - `vector` 底层使用连续的动态数组存储元素，当现有容量不足以容纳新元素时，会触发扩容
    - 分配一块更大的新内存（通常是当前容量的 1.5~2 倍）
    - 将旧内存中的元素复制 / 移动到新内存
    - 释放旧内存
    - 指向旧内存的迭代器、指针、引用会失效
1. `push_back()`和`emplace_back()`有什么区别？`emplace_back()`是怎么实现的？
    - `push_back()`：
        用于将一个已经构造好的对象复制或移动到容器中。
        如果传入的是临时对象，会先构造临时对象，再通过移动构造函数将其移动到容器（C++11 及以后）；如果传入的是已有对象，则会调用复制构造函数。
    - `emplace_back()`：
        直接在容器的内存空间中原地构造对象，避免了临时对象的创建和移动 / 复制操作。
        它接收的是对象构造函数的参数，而非对象本身，通过这些参数直接在容器末尾构造新元素。
## 2.2 list：✅
## 2.3 hash table：✅
## 2.4 deque

# 三、C++新特性
需要了解的新特性有智能指针、`lambada`表达式
## 3.1 智能指针

### 3.1.1 unique_ptr

`unique_ptr` 是 C++11 引入的智能指针，实现了**独占所有权**语义，用于管理动态分配的内存，确保同一时间只有一个指针拥有对资源的所有权。

#### 3.1.1.1 核心特性

1. **独占所有权**  
   同一时间只能有一个 `unique_ptr` 指向特定对象，所有权不可共享，这与 `shared_ptr` 的共享所有权形成鲜明对比。

2. **禁止复制操作**  
   - 复制构造函数和复制赋值运算符被显式禁用，防止所有权被复制
   - 错误示例：`unique_ptr<int> p2 = p1;`（编译错误）

3. **支持移动操作**  
   允许通过移动构造函数和移动赋值运算符转移所有权：
   - 移动后，原 `unique_ptr` 会被置为 `nullptr`
   - 示例：`unique_ptr<int> p2 = std::move(p1);`（p1 失去所有权，p2 获得所有权）

#### 3.1.1.2 实现要点

1. **禁用复制机制**  
   通过 `delete` 关键字显式删除复制构造和复制赋值运算符：
   ```cpp
   unique_ptr(const unique_ptr&) = delete;
   unique_ptr& operator=(const unique_ptr&) = delete;
   ```

2. **实现移动语义**  
   提供移动构造函数和移动赋值运算符，实现所有权的转移：
   ```cpp
   // 移动构造函数
   unique_ptr(unique_ptr&& other) noexcept 
       : ptr(other.ptr) {
       other.ptr = nullptr; // 原指针置空
   }
   
   // 移动赋值运算符
   unique_ptr& operator=(unique_ptr&& other) noexcept {
       if (this != &other) {
           delete ptr;       // 释放当前资源
           ptr = other.ptr;  // 转移所有权
           other.ptr = nullptr; // 原指针置空
       }
       return *this;
   }
   ```

3. **资源管理**  
   - 析构函数自动释放所管理的对象
   - 提供 `reset()` 方法显式释放资源或更换管理的对象
   - 提供 `release()` 方法释放所有权但不释放资源

#### 3.1.1.3 典型用法

```cpp
// 创建 unique_ptr
std::unique_ptr<int> ptr(new int(42));

// 移动所有权
std::unique_ptr<int> ptr2 = std::move(ptr); // ptr 变为 null

// 管理动态数组
std::unique_ptr<int[]> arr(new int[5]);

// 自定义删除器
auto deleter = [](int* p) { 
    delete p; 
};
std::unique_ptr<int, decltype(deleter)> ptr3(new int(10), deleter);
```

#### 3.1.1.4 优势总结

- **内存安全**：自动释放资源，避免内存泄漏
- **高性能**：相比 `shared_ptr` 无需维护引用计数，开销更小
- **明确所有权**：清晰表达资源的独占性，使代码意图更明确
- **灵活性**：可用于容器存储，作为函数返回值传递（通过移动语义）

### 3.1.2 shared_ptr

####  3.1.2.1 核心特点

`shared_ptr` 是 C++ 标准库提供的智能指针，实现了**共享所有权**机制：
- 多个 `shared_ptr` 可指向同一块动态分配的内存
- 通过**引用计数（reference count）** 跟踪共享该资源的指针数量
- 当最后一个指向资源的 `shared_ptr` 被销毁或重置时，内存会自动释放

####  3.1.2.2 实现原理

1. **内部组成**
- `T* ptr`：指向实际管理的对象（原始指针）
- `size_t* ref_count`：指向引用计数的指针，记录当前共享对象的 `shared_ptr` 数量

2. **核心接口**
- 构造函数：`shared_ptr(T *p)`（默认构造）、拷贝构造、移动构造
- 析构函数：`~shared_ptr()`
- 赋值运算符：拷贝赋值、移动赋值
- 访问运算符：`operator*()`（解引用）、`operator->()`
- 辅助方法：`get()`（获取原始指针）、`use_count()`（获取引用计数）、`swap()`（交换内容）

####  3.1.2.3 线程安全特性

- **部分线程安全**：
  - 标准库的 `std::shared_ptr` 保证**引用计数的修改是原子操作**（线程安全）
  - **不对管理的对象本身提供线程安全**（`T* ptr` 指向的对象），需要用户自行保证对象的线程安全

- **非线程安全场景**：
  - 简单实现可能不保证引用计数的线程安全
  - 多线程环境下操作同一个 `shared_ptr` 可能导致计数错乱

####  3.1.2.4 实现代码示例

```cpp
#include <iostream>
#include <utility> // for std::swap

template <typename T> 
class shared_ptr {
private:
  T* ptr;           // 指向管理的对象
  size_t* ref_count; // 引用计数指针

  // 释放资源
  void release() {
    if (ref_count) {
      (*ref_count)--;
      // 当引用计数为0时，彻底释放资源
      if (*ref_count == 0) {
        delete ptr;
        delete ref_count;
      }
      // 清空当前实例的指针
      ptr = nullptr;
      ref_count = nullptr;
    }
  }

public:
  // 构造函数：从原始指针构造
  explicit shared_ptr(T* p = nullptr) : ptr(p), ref_count(nullptr) {
    if (p) {
      ref_count = new size_t(1); // 初始化引用计数为1
    }
  }

  // 拷贝构造函数
  shared_ptr(const shared_ptr& other) 
      : ptr(other.ptr), ref_count(other.ref_count) {
    if (ref_count) { // 防止拷贝空对象
      (*ref_count)++;
    }
  }

  // 移动构造函数
  shared_ptr(shared_ptr&& other) noexcept 
      : ptr(other.ptr), ref_count(other.ref_count) {
    // 转移所有权后将源对象指针置空
    other.ptr = nullptr;
    other.ref_count = nullptr;
  }

  // 析构函数
  ~shared_ptr() {
    release();
  }

  // 拷贝赋值运算符
  shared_ptr& operator=(const shared_ptr& other) {
    // 防止自赋值
    if (this != &other) {
      // 先释放当前资源
      release();
      // 拷贝新资源
      ptr = other.ptr;
      ref_count = other.ref_count;
      if (ref_count) {
        (*ref_count)++;
      }
    }
    return *this;
  }

  // 移动赋值运算符
  shared_ptr& operator=(shared_ptr&& other) noexcept {
    if (this != &other) {
      // 释放当前资源
      release();
      // 转移所有权
      ptr = other.ptr;
      ref_count = other.ref_count;
      // 源对象指针置空
      other.ptr = nullptr;
      other.ref_count = nullptr;
    }
    return *this;
  }

  // 重载解引用运算符
  T& operator*() const {
    return *ptr;
  }

  // 重载->运算符
  T* operator->() const {
    return ptr;
  }

  // 获取原始指针
  T* get() const {
    return ptr;
  }

  // 获取当前引用计数
  size_t use_count() const {
    return ref_count ? *ref_count : 0;
  }

  // 交换两个shared_ptr的内容
  void swap(shared_ptr& other) {
    std::swap(ptr, other.ptr);
    std::swap(ref_count, other.ref_count);
  }
};

// 辅助函数：创建shared_ptr（类似std::make_shared）
template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
  return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
```

####  3.1.2.5 make_shared 相关知识点

`make_shared` 是创建 `shared_ptr` 的推荐方式，具有以下优势：

1. **内存分配更高效**：
   - 传统方式（`new` + `shared_ptr`）：需要两次内存分配（对象本身 + 引用计数）
   - `make_shared` 方式：一次性分配连续内存，同时存储对象和引用计数（包括控制信息），减少内存分配开销

2. **提高异常安全性**：
   - 在将指针作为参数传递等场景下，避免因异常抛出导致的内存泄漏风险
   - 例如：`func(shared_ptr<T>(new T), other_func())` 可能因函数参数求值顺序导致内存泄漏，而 `func(make_shared<T>(), other_func())` 可避免此问题

3. **简化代码**：
   - 无需显式使用 `new` 操作符
   - 语法：`make_shared<类型>(构造参数)`，使代码更简洁直观

### 3.1.3 weak_ptr

`weak_ptr` 是 C++ 智能指针库中的重要组成部分，主要用于解决 `shared_ptr` 可能导致的循环引用问题。它本身不拥有对象的所有权，仅作为 `shared_ptr` 的观察者存在，持有被观察对象的弱引用，不会影响被观察者的生命周期。

#### 3.1.3.1 主要特性

1. **不控制对象生命周期**  
   `weak_ptr` 不会增加所指向对象的引用计数，当最后一个 `shared_ptr` 被销毁时，即使有 `weak_ptr` 指向该对象，对象也会被释放。

2. **解决循环引用**  
   当两个对象互相持有 `shared_ptr` 时会形成循环引用，导致引用计数无法归零，引发内存泄漏。使用 `weak_ptr` 替代其中一个 `shared_ptr` 可打破这种循环。

3. **需转换为 `shared_ptr` 才能访问对象**  
   `weak_ptr` 本身不能直接访问对象，必须通过 `lock()` 方法转换为 `shared_ptr`，这确保了在访问时对象仍然存在。

#### 3.1.3.2 实现原理

##### 控制块（Control Block）

`weak_ptr` 与 `shared_ptr` 共享同一个控制块来管理对象生命周期，控制块包含以下核心信息：
- **强引用计数（strong count）**：跟踪持有对象所有权的 `shared_ptr` 数量，当减为 0 时对象被销毁。
- **弱引用计数（weak count）**：跟踪观察对象的 `weak_ptr` 数量（包括控制块自身的引用），当减为 0 时控制块被销毁。
- 指向对象的指针、删除器（deleter）和分配器（allocator）。

##### 核心机制

1. **初始化与关联**  
   当 `weak_ptr` 从 `shared_ptr` 初始化或赋值时，会指向其控制块并将弱引用计数 +1，但不影响强引用计数。

2. **对象访问机制**  
   通过 `lock()` 方法转换为 `shared_ptr` 才能访问对象：
   - 检查强引用计数是否 > 0（对象是否存活）。
   - 若存活，返回新的 `shared_ptr` 并将强引用计数 +1，确保访问期间对象不被销毁。
   - 若已销毁，返回空的 `shared_ptr`。

3. **生命周期管理**  
   - 最后一个 `shared_ptr` 销毁时（强引用计数 = 0），对象被销毁，但控制块保留（可能还有 `weak_ptr` 引用）。
   - 最后一个 `weak_ptr` 销毁时（弱引用计数 = 0），控制块被释放，彻底清理内存。

4. **循环引用解决原理**  
   在循环引用场景中，`weak_ptr` 仅增加弱引用计数，不影响强引用计数。当外部 `shared_ptr` 销毁时，强引用计数可正常减为 0，对象被销毁，打破循环。

#### 3.1.3.4 简化实现示例

```cpp
// 控制块结构（简化版）
template <typename T>
struct ControlBlock {
    int strong_count;  // 强引用计数
    int weak_count;    // 弱引用计数
    T* object;         // 指向实际对象
    // ... 其他成员（删除器等）
};

// weak_ptr 简化实现
template <typename T>
class weak_ptr {
private:
    ControlBlock<T>* cb;  // 指向控制块

public:
    // 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& sp) : cb(sp.cb) {
        if (cb) cb->weak_count++;  // 弱引用计数+1
    }

    // 转换为 shared_ptr（lock() 方法）
    shared_ptr<T> lock() const {
        if (cb && cb->strong_count > 0) {
            // 对象存活，返回 shared_ptr 并增加强引用计数
            return shared_ptr<T>(cb);
        }
        return shared_ptr<T>();  // 对象已销毁，返回空
    }

    // 析构函数
    ~weak_ptr() {
        if (cb) {
            cb->weak_count--;
            if (cb->weak_count == 0 && cb->strong_count == 0) {
                delete cb;  // 弱引用计数为0且对象已销毁，释放控制块
            }
        }
    }
};
```

## 3.2 `lambada`表达式

# 四、设计模式
## 4.1 单例模式：✅

### 4.1.1 单例模式实现方式之一：
1. 私有化构造函数，删除拷贝构造函数，删除复制运算符函数
2. 提供全局访问点：
    - 实现返回类唯一实例的静态成员函数`getInstance()`
    - 函数内初始化一个局部静态成员变量`instance`
    - 函数返回局部静态成员变量`instance`的引用

```cpp
class Singleton {
private:
  Singleton() = default; // 构造函数私有化,并且使用默认实现
  Singleton(const Singleton &a) = delete;            // 删除拷贝构造
  Singleton &operator=(const Singleton &a) = delete; // 删除复制运算符函数
public:
  static Singleton& getInstance() {
    static Singleton instance;
    return instance;
  }
};
```

### 4.1.2 单例模式注意事项
1. **类的静态成员变量需要在类外进行初始化**。若是使用*返回唯一实例指针*的方式来实现单例模式的化需要在类内定义静态成员指针并在类外初始化
2. **类的静态成员函数默认情况下只能操作静态成员变量**。因为静态成员函数不属于类分身，若要操作非静态成员可以向函数内传实例或者this指针

### 4.1.3 单例模式线程安全问题
1. 上述代码在**C++11标准及以上**是线程安全的。因为 C++11 规定，静态局部变量的初始化会在首次访问时进行，且编译器会自动加入同步机制，确保即使多线程同时调用`getInstance()`，也只会初始化一次实例。因此确实能保证全局唯一。
2. "返回指针的实现是否线程安全"需要分情况讨论：
    - 饿汉式：在程序启动时就初始化静态实例，如`static Singleton* instance = new Singleton();`，返回指针的方式也是线程安全的
    - 懒汉式：首次调用时才初始化，如`if (instance == nullptr) { instance = new Singleton(); }）`，且未加锁，则不是线程安全的
3. 即使类对象的创建是线程安全的，对于类内的普通成员来讲，在多线程访问操作时依旧会发生数据竞争的问题

# 五、并发组件
## 5.1 线程池
# 六、计算机网络
需要熟悉`HTTP`,`TCP`,`UDP`,`IP`等协议以及收集面试中常见的问题，对于`TCP`,`UDP`还要知道他们的编程实现。对于`OSI`中的应用层、传输层、网络层等其他知识也需要了解
## 6.1 UDP
## 6.2 TCP
## 6.3 HTTP
## 6.4 IP
# 七、数据库
学会SQL数据库常见的增删查改操作
# 八、常见开发工具的命令
## 8.1 Linux常用命令
## 8.2 git常用命令
### 8.2.1 git init
初始化新的 Git 仓库
- 常用参数/用法
    - `git init`：在当前目录创建一个新的、空的 Git 仓库
    - `git init /path/to/your/project`：在`/path/to/your/project`创建一个新的、空的 Git 仓库
    - `git init -b main`：初始化仓库，并设置默认分支为 'main'
    - `git init --bare /srv/my-project.git`：创建裸仓库，保证团队协作和自动化流程的可靠性与一致性。
### 8.2.1 git add
将文件添加到暂存区
- 基本用法：`git add <文件/目录>`
- 常用参数 / 用法：
    - `git add .`：添加**当前目录**所有修改到暂存区
    - `git add --all` 或 `-A`：添加**整个 Git 仓库中**所有的修改到暂存区
    - `git add -u`：只添加已跟踪文件的修改和删除（不包括新增文件）
    - `git add src/`：添加整个目录的修改
    - `git add README.md`：添加单个文件
## 8.3 Cmake常用命令