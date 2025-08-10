#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include<string>
#include <stdexcept>  

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
            throw std::out_of_range("vector::at: Index out of range");
        }
        return this->head[pos];
    }

    T& operator[](size_t index) 
    {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }
};

#endif