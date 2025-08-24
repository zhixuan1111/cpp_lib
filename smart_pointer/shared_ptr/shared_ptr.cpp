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
  explicit shared_ptr(T *p) : ptr(p), ref_count(nullptr) {
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