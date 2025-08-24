# shared_ptr知识点
## shared_ptr实现原理
1. **核心特点**
共享所有权。多个 `shared_ptr` 可以指向同一块动态分配的内存，内部通过引用计数（reference count）机制跟踪有多少个指针共享该资源。当最后一个指向该资源的 shared_ptr 被销毁或重置时，内存会自动释放。
2. **简易实现**
- `T* ptr`：指向实际管理的对象（原始指针）
- `size_t* ref_count`：指向一个整数的指针，用于记录当前有多少SharedPtr 实例在共享 ptr 指向的对象
- `shared_ptr(T *p)`：默认构造函数
- `shared_ptr(const shared_ptr &other)`：拷贝构造函数
- `shared_ptr(shared_ptr &&other)`：移动构造函数
- `~shared_ptr()`：析构函数
-  `shared_ptr &operator=(const shared_ptr &other)`：拷贝赋值运算符函数
- `shared_ptr &operator=(shared_ptr &&other)`：移动赋值运算符函数
- `T &operator*()`：重载解引用
- `T *operator->()`：重载`->`
## 线程安全问题
- **部分线程安全**：标准库的 `std::shared_ptr` 保证引用计数的修改是原子操作（线程安全），**但对管理的对象本身不提供线程安全**(指的是`T* ptr`),需要用户自己保证对象的线程安全。
- **非线程安全**：简单实现可能不保证引用计数的线程安全，多线程环境下操作同一个 `shared_ptr` 可能导致计数错乱。

## 代码
```cpp
#include <iostream>
template <typename T> class shared_ptr {
private:
  T *ptr;
  size_t *ref_count;
  void release() {
    if (ref_count) {
      (*ref_count)--;
      // 判断是否需要彻底释放资源
      if (*ref_count == 0) {
        /* code */
        delete ptr;
        delete ref_count;
      }
      // 清空当前实例的指针
      ptr = nullptr;
      ref_count = nullptr;
    }
  }

public:
  // 默认构造函数
  shared_ptr(T *p) : ptr(p), ref_count(nullptr) {
    if (p) {
      ref_count = new size_t(1); // 给引用计数赋初始值
    }
  }

  // 拷贝构造函数
  shared_ptr(const shared_ptr &other)
      : ptr(other.ptr), ref_count(other.ref_count) {
    if (ref_count) { // 防止被拷贝的对象是空的，避免对空指针进行解引用操作
      (*ref_count)++;
    }
  }
  // 移动构造函数
  shared_ptr(shared_ptr &&other) : ptr(other.ptr), ref_count(other.ref_count) {
    other.ptr = nullptr;
    other.ref_count = nullptr;
  }

  // 析构函数
  ~shared_ptr() { release(); }

  // 拷贝赋值运算符函数
  shared_ptr &operator=(const shared_ptr &other) {
    // 需要防止自己复制自己
    if (this != other) {
      ptr = other.ptr;
      ref_count = other.ref_count;
    }
    if (ref_count) { // 防止被拷贝的对象是空的，避免对空指针进行解引用操作
      (*ref_count)++;
    }
    return *this;
  }

  // 移动赋值运算符函数
  shared_ptr &operator=(shared_ptr &&other) {
    // 需要防止自己复制自己
    if (this != &other) {
      release(); // 如果当前实例正在管理某个资源,不释放就直接覆盖指针的话，会导致原资源的引用计数丢失，造成内存泄漏
      ptr = other.ptr;
      ref_count = other.ref_count;
      other.ptr = nullptr;
      other.ref_count = nullptr;
    }
    return *this;
  }

  // 重载解引用运算符
  T &operator*() const { return *ptr; }

  // 重载->运算符函数
  T *operator->() const { return ptr; }
  // 获取原始指针
  T *get() const { return ptr; }

  // 获取当前引用计数
  size_t use_count() const { return ref_count ? *ref_count : 0; }
  // 交换两个 SharedPtr 的内容
  void swap(SharedPtr &other) {
    std::swap(ptr, other.ptr);
    std::swap(ref_count, other.ref_count);
  }
};
// 辅助函数：创建 SharedPtr
template <typename T, typename... Args>
shared_ptr<T> make_shared(Args &&...args) {
  return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
```

## make_shared有关知识点
`make_shared` 属于 C++ 智能指针体系的一部分，它是一个函数模板，主要用于创建 `std::shared_ptr` 智能指针。具体来说有以下几个核心作用：
1. **内存管理更高效**：`make_shared` 会**一次性分配一块内存**，同时存储对象本身和引用计数，而单独使用 `new` 配合 `std::shared_ptr` 构造函数需要两次内存分配（一次给对象，一次给引用计数），因此 `make_shared` 能减少内存分配开销。
- **传统方式（`new` + `shared_ptr`）**：两次分配是独立的，操作系统需要分别处理两次内存申请，每次都要在内存管理系统中查找可用内存块、更新内存分配表等。
  - 第一次：通过 `new T(args)` 为对象本身分配内存（存储 `T` 类型的实例数据）。
  - 第二次：`shared_ptr` 内部需要为 "引用计数"（记录指针被多少个 `shared_ptr` 共享）分配一块额外的内存。
- **make_shared 方式**：会一次性分配一块连续的内存，同时容纳两部分内容：
  - 对象本身的数据（`T` 类型的实例）。
  - 引用计数（以及 `shared_ptr` 所需的其他控制信息，如删除器等）。
2. **提高异常安全性**：在需要将指针作为参数传递等场景下，使用 `make_shared` 可以避免因异常抛出导致的内存泄漏风险。
3. **简化代码**：无需显式使用 `new` 操作符，直接通过 `make_shared<类型>(构造参数)` 的形式即可创建智能指针，使代码更简洁。