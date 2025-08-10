#include <iostream>
#include<string>

template<typename T>
class vector
{
private:
    /* data */
    T* head;
    size_t size;
    size_t capacity;
public:
    vector(size_t nums);
    ~vector();
    T& at(size_t pos); //访问元素；
    size_t getSize();
    size_t getCapacity();
    bool pushBack(int value);


};
template<typename T>
vector<T>::vector(size_t num)
{
    this->head = new T(num);
    this->capacity = num;
    for (size_t i = 0; i < num; i++)
    {
        head[i] = T();
    }
    
}
template<typename T>
vector<T>::~vector()
{
}

template<typename T>
size_t vector<T>::getSize()
{
    return this->size;
}

template<typename T>
size_t vector<T>::getCapacity()
{
    return this->capacity;
}

template<typename T>
T& vector<T>::at(size_t pos)
{
    // if(pos > this->size-1 || pos < 0)
    // {
    //     std::cout<<"index out of range"<<std::endl;
    //     return -1;
    // }
    
    // {
        int i=0;
        while (i < pos)
        {
            i++;
        }
        return this->head[i];
    // }
}

template<typename T>
bool vector<T>::pushBack(int value)
{
    return true;
}
int main()
{
    vector<std::string> a(5);
    a.at(1) = "1";
    std::cout<< a.at(1)<<std::endl;
    std::cout<< a.at(5)<<std::endl;
    return 0;
}