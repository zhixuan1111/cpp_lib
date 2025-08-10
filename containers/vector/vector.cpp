#include <iostream>
#include<string>
#include <stdexcept>  // 用于std::out_of_range

template<typename T>
class vector
{
private:
    T* head;
    size_t size;
    size_t capacity;
public:

    vector<T>::vector(size_t num)
    {
        this->head = new T(num);
        this->capacity = num;
        for (size_t i = 0; i < num; i++)
        {
            head[i] = T();
        }  
    }

    vector<T>::~vector()
    {
        delete[] head;
    }
    
    size_t vector<T>::getSize()
    {
        return this->size;
    }

    size_t vector<T>::getCapacity()
    {
        return this->capacity;
    }

    T& vector<T>::at(size_t pos)
    {
        if (pos >= this->size)
        {
            throw std::out_of_range("vector::at: 索引越界");
        }
        return this->head[pos];
    }
};

int main()
{
    vector<std::string> a(5);
    a.at(1) = "1";
    std::cout<< a.at(1)<<std::endl;
    std::cout<< a.at(5)<<std::endl;
    return 0;
}