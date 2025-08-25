template <class T> class unique_ptr {
private:
  T *ptr; // 原始指针

public:
  // 构造函数
  explicit unique_ptr(T *p = nullptr) : ptr(p) {}

  // 禁止复制构造和复制赋值
  unique_ptr(const unique_ptr &) = delete;            // 禁用复制构造
  unique_ptr &operator=(const unique_ptr &) = delete; // 禁用复制赋值

  // 支持移动构造和移动赋值
  unique_ptr(unique_ptr &&other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr; // 将原指针置为 nullptr
  }

  unique_ptr &operator=(unique_ptr &&other) noexcept {
    if (this != &other) {
      delete ptr;          // 先释放当前所持有的资源
      ptr = other.ptr;     // 转移所有权
      other.ptr = nullptr; // 将原指针置为 nullptr
    }
    return *this;
  }

  // 析构函数
  ~unique_ptr() {
    delete ptr; // 当 unique_ptr 被销毁时释放资源
  }

  // 解引用操作符
  T &operator*() const { return *ptr; }
  T *operator->() const { return ptr; }
};
