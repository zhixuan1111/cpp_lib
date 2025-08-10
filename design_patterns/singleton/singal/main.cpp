#include <iostream>
using namespace std;

class Singleton 
{
private:
    static Singleton* instance;
    Singleton() {}  // 私有构造函数，防止外部直接创建对象
    

public:
    static Singleton* getInstance() 
    {
        if (instance == nullptr) 
        {
            instance = new Singleton();
        }
        // 返回单例对象的指针
        return instance;
    }

    void printMessage() 
    {
        std::cout << "This is a singleton instance." << std::endl;
    }
    static int a;
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;   //静态成员外部初始化书写的固定格式：<类型> <类名>::<静态成员变量名> = <初始值>;
int Singleton::a = 1;
int main() 
{
    // 调用 getInstance 函数获取单例对象的指针
    Singleton* obj = Singleton::getInstance();
    // 使用获取到的指针调用类的成员函数
    obj->printMessage();

    // 再次获取单例对象的指针，确保是同一个实例
    Singleton* anotherObj = Singleton::getInstance();
    // 检查两个指针是否指向同一个对象
    if (obj == anotherObj) {
        std::cout << "Both pointers refer to the same singleton instance." << std::endl;
    }
    cout<<Singleton::a<<endl;


    return 0;
}

// 1.将构造函数私有化
// 2.声明一个私有的静态成员变量，该变量是这个类的指针类型
// 3.在类外初始化该静态成员指针“a”，并赋初始值nullptr
// 4.类内pubilc下实现以下静态成员函数来获取唯一类实例。如果“a”没有被实例过指针依旧是nullptr，则实例一下；如果不是nullptr则直接返回指针