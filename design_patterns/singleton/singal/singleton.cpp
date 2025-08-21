#include <iostream>

class Singleton {
private:
  Singleton() = default; // 构造函数私有化,并且使用默认实现
  Singleton(const Singleton &a) = delete;            // 删除拷贝构造
  Singleton &operator=(const Singleton &a) = delete; // 删除复制运算符函数
public:
  static Singleton &getInstance() {
    static Singleton instance;
    return instance;
  }
};
