# Lambda 表达式

C++ 的 Lambda 表达式是一种可以定义匿名函数的语法，主要用于简化代码、提高可读性和减少函数对象的使用。它允许在需要函数的地方直接定义函数，特别适合作为算法的回调函数或临时操作。


## 一、基本语法

```cpp
[capture](参数列表) -> 返回类型 {
    函数体
};
```

- **capture（捕获列表）**：定义如何访问外部作用域中的变量（按值或按引用）
- **参数列表**：与普通函数的参数列表语法相同，可省略（无参数时）
- **返回类型**：可省略，编译器能自动推导返回类型时无需显式指定
- **函数体**：包含具体的执行逻辑


## 二、核心用法详解

### 2.1 捕获列表（外部变量访问规则）

捕获列表控制 lambda 如何访问定义它的作用域中的变量，主要有以下几种形式：

| 捕获方式 | 说明 | 示例 |
|---------|------|------|
| `[x]` | 按值捕获变量 x | `[x]() { return x * 2; }` |
| `[&x]` | 按引用捕获变量 x | `[&x]() { x++; }` |
| `[=]` | 按值捕获所有外部变量 | `[=]() { return a + b; }` |
| `[&]` | 按引用捕获所有外部变量 | `[&]() { a++; b++; }` |
| `[x, &y]` | 混合捕获：x 按值，y 按引用 | `[x, &y]() { y += x; }` |
| `[=, &x]` | 大部分按值，x 按引用 | `[=, &x]() { x += a + b; }` |
| `[&, x]` | 大部分按引用，x 按值 | `[&, x]() { a += x; }` |
| `[]` | 不捕获任何变量 | `[]() { return 42; }` |

#### 按值捕获的特殊说明：
- 按值捕获的变量在 lambda 内部默认是只读的
- 若需修改副本，需使用 `mutable` 关键字（不影响外部原变量）：
  ```cpp
  int x = 10;
  auto f = [x]() mutable {
      x++;          // ✅ 允许修改内部副本
      return x;     // 返回 11，外部 x 仍为 10
  };
  ```


### 2.2 参数列表

- 语法与普通函数相同，支持参数类型、默认参数等特性
- 无参数时可省略参数列表的括号：
  ```cpp
  [] { std::cout << "无参数的 lambda" << std::endl; }();
  ```
- 支持可变参数（C++11 起）：
  ```cpp
  auto print = [](auto... args) {
      (std::cout << ... << args) << std::endl;
  };
  print("Hello", " ", "Lambda", "!"); // 输出：Hello Lambda!
  ```


### 2.3 返回类型

- 多数情况下，编译器可自动推导返回类型，无需显式指定：
  ```cpp
  auto add = [](int a, int b) { return a + b; }; // 自动推导返回 int
  ```
- 当返回类型有歧义（如不同分支返回不同类型）时，必须显式指定：
  ```cpp
  auto convert = [](bool flag) -> double {
      if (flag) return 10;    // int 隐式转换为 double
      else return 3.14;       // 直接返回 double
  };
  ```


### 2.4 泛型 Lambda（C++14 起）

支持使用 `auto` 作为参数类型，实现泛型行为：

```cpp
// 泛型加法函数
auto sum = [](auto a, auto b) { return a + b; };

int i = sum(10, 20);          // 30（int）
double d = sum(3.14, 2.71);   // 5.85（double）
std::string s = sum("Hello", " World"); // "Hello World"（字符串拼接）
```


## 三、底层实现原理

Lambda 表达式在编译器内部会被转换为一个**匿名类（闭包类，closure class）**，lambda 对象本质上是该类的实例。**lambda = 匿名类 + operator() 重载**，调用 `lambda` 相当于调用这个对象的 `operator()`。

### 3.1 普通 Lambda（C++11）

```cpp
// 原始 lambda 表达式
int x = 10;
auto func = [x](int y) { return x + y; };
```

编译器会生成类似下面的代码：
```cpp
// 编译器生成的匿名类（闭包类）
struct __Lambda1 {
private:
    int x;  // 按值捕获的变量作为成员变量
public:
    // 构造函数：初始化捕获的变量
    __Lambda1(int x_) : x(x_) {}
    
    // 重载 operator()，实现函数调用
    int operator()(int y) const {  // 默认是 const 成员函数
        return x + y;
    }
};

// 创建 lambda 对象
__Lambda1 func(x);
```

- `mutable` 关键字的作用是移除 `operator()` 的 `const` 属性：
  ```cpp
  struct __Lambda2 {
    int x;
    __Lambda2(int x_) : x(x_) {}
    // mutable 使 operator() 不再是 const
    int operator()(int y) { 
        x++; 
        return x + y; 
    }
  };
  ```


### 3.2 泛型 Lambda（C++14 起）

泛型 lambda 会被转换为包含模板成员函数的闭包类：

```cpp
// 泛型 lambda
auto sum = [](auto a, auto b) { return a + b; };
```

编译器生成的代码类似：
```cpp
struct __Lambda3 {
    // 模板化的 operator()
    template <typename T1, typename T2>
    auto operator()(T1 a, T2 b) const {
        return a + b;
    }
};

__Lambda3 sum;
```


## 四、关键特性总结

1. **匿名性**：没有函数名，通常通过 `auto` 变量捕获
2. **捕获机制**：灵活控制外部变量的访问方式（值/引用）
3. **简洁性**：在需要函数的地方直接定义，减少代码跳转
4. **效率**：与手写函数对象性能相当，无额外开销
5. **生命周期**：lambda 对象的生命周期与普通变量相同

Lambda 表达式特别适合：
- 作为标准算法库（如 `std::for_each`、`std::sort`）的回调函数
- 实现简短的功能逻辑，避免定义命名函数
- 封装与上下文相关的操作，保持代码局部性