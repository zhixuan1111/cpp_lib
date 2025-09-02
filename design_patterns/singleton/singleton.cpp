#include <iostream>

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
