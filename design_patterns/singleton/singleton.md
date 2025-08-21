# 单例模式知识点汇总
## 实现方式之一：
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
## 注意事项
1. **类的静态成员变量需要在类外进行初始化**。若是使用*返回唯一实例指针*的方式来实现单例模式的化需要在类内定义静态成员指针并在类外初始化
2. **类的静态成员函数默认情况下只能操作静态成员变量**。因为静态成员函数不属于类分身，若要操作非静态成员可以向函数内传实例或者this指针

## 线程安全问题
1. 上述代码在**C++11标准及以上**是线程安全的。因为 C++11 规定，静态局部变量的初始化会在首次访问时进行，且编译器会自动加入同步机制，确保即使多线程同时调用`getInstance()`，也只会初始化一次实例。因此确实能保证全局唯一。
2. "返回指针的实现是否线程安全"需要分情况讨论：
    - 饿汉式：在程序启动时就初始化静态实例，如`static Singleton* instance = new Singleton();`，返回指针的方式也是线程安全的
    - 懒汉式：首次调用时才初始化，如`if (instance == nullptr) { instance = new Singleton(); }）`，且未加锁，则不是线程安全的
3. 即使类对象的创建是线程安全的，对于类内的普通成员来讲，在多线程访问操作时依旧会发生数据竞争的问题