#include <iostream>
#include <cstring>


class stack
{
private:
    /* data */
    int capcity;
    int* a=nullptr;
    int size;
public:
    stack();    //默认构造
    stack(int cap); //带参构造，参数为容量
    stack(const stack& other);  //拷贝构造
    stack(stack&& other)noexcept;   //移动构造
    stack& operator=(const stack& other);   //拷贝运算符函数，复制资源。需要返回引用
    stack& operator=(stack&& other) noexcept;   //移动运算符函数，窃取资源
    // 移动复制、构造与拷贝赋值、构造的区别：前者需要返回对象，而且需要判断传入参数是否与当前参数相等！
    ~stack();
    bool empty();
    bool reszie(int new_capcity);
    void push(int value);    //末尾插入元素
    void pop(); //移除栈顶元素
    int top(); //返回栈顶元素
    void show();
    void printCapAndSize();

};

stack::stack()
{
    this->a=new int[100];
    this->capcity=100;
    this->size=0;
}

stack::stack(int cap):capcity(cap)
{
    this->a=new int[capcity];
    this->size=0;
}

stack::stack(const stack& other)
{
    this->capcity=other.capcity;
    this->size=other.size;
    this->a=new int[this->capcity];
    memcpy(this->a,other.a,this->size*sizeof(int));
}

stack::stack(stack&& other)noexcept
{
    this->capcity=other.capcity;
    this->size=other.size;
    this->a=other.a;
    other.capcity=0;
    other.size=0;
    other.a=nullptr;
}

stack::~stack()
{
    delete[] a;
}

bool stack::empty()
{
    return this->size==0;
}

void stack::show()
{
    if (this->size==0)
    {
        std::cout<<"no any element!"<<std::endl;
        return;
    }
    for (int i=0;i<size;i++)
    {
        std::cout<<a[i]<<" ";
    }
    std::cout<<std::endl;
}

bool stack::reszie(int new_capcity)
{
    if(new_capcity<=capcity)
    {
        std::cout<<"new capcity must bigger than capcity!"<<std::endl;
        return false;
    }
    int* b=new int(new_capcity);
    std::memcpy(b, a, capcity*sizeof(int));
    delete[] a;
    this->a=b;
    this->capcity=new_capcity;
    return true;
}

void stack::printCapAndSize()
{
    std::cout<<"current capcitiy = "<<this->capcity<<" current size = "<<this->size<<std::endl;
}

void stack::push(int value)
{
    if(this->size>=this->capcity)
    {
        this->reszie(2*this->capcity);
    }

    a[size]=value;
    this->size++;
}

void stack::pop()
{
    this->size--;
}

int stack::top()
{
    return this->a[this->size-1];
}

int main()
{
    stack a;
    a.push(1);
    a.push(2);
    a.push(3);
    // a.printCapAndSize();
    // a.show();
    // a.pop();
    // a.show();
    // a.printCapAndSize();
    stack b=std::move(a);
    b.show();


    return 0;
}