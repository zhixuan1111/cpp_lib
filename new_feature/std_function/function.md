# std::function 详解

`std::function` 是 C++11 标准库 `<functional>` 头文件中引入的**通用函数封装器**，核心作用是统一管理各类「可调用对象」，实现不同类型可调用对象的存储、复制与调用，相当于一个“智能函数容器”。


## 一、核心定义与本质
`std::function` 的本质是通过**类型擦除（Type Erasure）** 技术，屏蔽不同可调用对象的类型差异，提供统一的接口来存储和调用它们。其模板定义格式为：
```cpp
template <typename Ret, typename... Args>
class function<Ret(Args...)>;
```
- `Ret`：可调用对象的返回类型
- `Args...`：可调用对象的参数类型列表（可变参数，支持0个或多个参数）

例如：
- `std::function<int(int, int)>`：表示“接受两个 `int` 参数、返回 `int`”的可调用对象
- `std::function<void()>`：表示“无参数、无返回值”的可调用对象


## 二、支持的可调用对象类型
`std::function` 可存储几乎所有符合“签名匹配”的可调用对象，包括以下5类常见场景：

### 2.1 普通函数
直接存储全局函数或命名空间内的普通函数，只需保证函数签名与 `std::function` 模板参数匹配。
```cpp
int add(int a, int b) {return a + b;}
std::function<int(int, int)> func = add;
```

### 2.2 函数指针
存储指向普通函数的指针，用法与普通函数类似，本质是通过指针间接调用函数。
```cpp
// 普通函数
int multiply(int a, int b) {return a * b;}
// 定义函数指针（签名：int(int, int)）
int (*func_ptr)(int, int) = multiply;
// 用 std::function 封装函数指针
std::function<int(int, int)> func = func_ptr;
```

### 2.3 Lambda 表达式
Lambda 表达式是匿名函数，其类型是编译器生成的“闭包类”，`std::function` 可直接存储符合签名的 Lambda（包括捕获外部变量的 Lambda）。
```cpp
std::function<int(int, int)> func = [](int a, int b) {return a - b;};
```

### 2.4 仿函数（函数对象）
仿函数是“重载了 `operator()` 的类/结构体对象”，`std::function` 可存储该类的实例，调用时本质是调用实例的 `operator()`。
```cpp
// 仿函数类（重载 operator()，签名：int(int, int)）
struct Divide {
    int operator()(int a, int b) { return a / b; }
};
std::function<int(int,int)> f = Divide();
```


### 2.5 std::bind 绑定的结果
`std::bind` 用于“绑定函数参数、调整参数顺序”，其返回的“绑定对象”也是可调用对象，可直接存储到 `std::function` 中。
```cpp
auto bound = std::bind(multiply, 10, std::placeholders::_1);
std::function<int(int)> f = bound;
std::cout << f(5); // 相当于 multiply(10, 5) = 50
```


## 三、常见用途场景
`std::function` 的核心价值是“统一可调用对象的接口”，主要用于以下3类场景：

### 3.1 作为回调函数
在需要“延迟执行”或“外部注入逻辑”的场景中，`std::function` 是传递回调函数的最佳选择（如 GUI 按钮点击回调、异步任务完成回调等）。
```cpp
void runCallback(std::function<void(int)> cb) {
    cb(42);
}

runCallback([](int x){ std::cout << "Lambda: " << x << "\n"; });
runCallback(printInt); // 普通函数也能传
```


### 3.2 存储不同类型的可调用对象
当需要将“不同类型但签名相同”的可调用对象存入容器（如 `std::vector`）时，`std::function` 是唯一可行的方案（直接用 `auto` 或模板无法实现容器存储）。
```cpp
int add(int a, int b) { return a + b; }
struct Multiply { int operator()(int a, int b) { return a * b; } };

// 定义存储 "int(int, int)" 签名可调用对象的容器
std::vector<std::function<int(int, int)>> func_list;

// 存入不同类型的可调用对象
func_list.push_back(add);                  // 普通函数
func_list.push_back([](int a, int b) {     // Lambda 表达式
    return a - b;
});
func_list.push_back(Multiply());           // 仿函数
```


### 3.3 延迟执行与任务调度
将可调用对象存储到 `std::function` 中，在需要的时候再触发调用，实现“任务延迟执行”（如线程池任务、定时器任务等）。
```cpp
std::function<int()> f;
{
    int x = 10;
    f = [x]() { return x + 5; };
}
std::cout << f() << std::endl; // 输出 15
```


## 四、注意事项与性能考量
### 4.1 类型擦除的代价
`std::function` 底层通过“类型擦除”实现通用存储，因此相比直接使用函数指针、`auto` 或模板，存在两点额外开销：
- **内存开销**：需存储可调用对象本身 + 类型信息（用于后续调用），内存占用略高。
- **调用开销**：调用时需通过“虚函数间接调用”或“函数指针跳转”，比直接调用略慢（但通常在可接受范围内，除非是高频调用场景）。


### 4.2 轻量级场景优先用 `auto` 或模板
如果可调用对象的类型已知（如 Lambda 表达式），且无需存储到容器或作为函数参数传递，优先用 `auto` 声明变量，避免 `std::function` 的额外开销：
```cpp
// 推荐：用 auto 存储 Lambda，无类型擦除开销
auto lambda = [](int x) { return x * x; };
lambda(5); // 直接调用，效率最高

// 不推荐：仅存储单个 Lambda 却用 std::function，浪费开销
std::function<int(int)> func = lambda;
```

如果需要编写通用函数接受可调用对象，优先用模板参数，而非 `std::function`，同样能避免类型擦除：
```cpp
// 模板函数：接受任意可调用对象，无类型擦除开销
template <typename Callable>
void invoke(Callable&& cb, int x) {
    cb(x);
}

int main() {
    invoke([](int x) { std::cout << x * 2 << std::endl; }, 3); // 输出：6
    return 0;
}
```


### 4.3 空 `std::function` 的调用风险
未初始化的 `std::function` 是“空的”（可通过 `operator bool()` 判断），直接调用空的 `std::function` 会抛出 `std::bad_function_call` 异常，需提前检查：
```cpp
std::function<int(int)> func; // 空的 std::function

if (func) { // 检查是否有效
    func(5); // 不会执行
} else {
    std::cout << "std::function 未初始化！" << std::endl;
}
```