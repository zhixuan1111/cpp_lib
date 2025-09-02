# `shared_ptr`实现代码示例  

回到[主文档 3.1.2 shared_ptr](../../../README.md#312-shared_ptr)

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

回到[主文档 3.1.2 shared_ptr](../../../README.md#312-shared_ptr)