#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include<string>
#include <stdexcept>  

#include <stdexcept> // 用于异常处理

template<typename T>
class vector
{
private:
    T* head;       // 指向动态数组的指针
    size_t size;   // 当前元素数量
    size_t capacity;// 容量（可容纳的最大元素数量）

    // 辅助函数：扩容
    void reserve(size_t new_capacity)
    {
        if (new_capacity <= capacity) return;
        
        // 分配新的内存空间
        T* new_head = new T[new_capacity];
        
        // 复制现有元素
        for (size_t i = 0; i < size; ++i)
        {
            new_head[i] = head[i];
        }
        
        // 释放旧内存
        delete[] head;
        
        // 更新指针和容量
        head = new_head;
        capacity = new_capacity;
    }

public:
    // 构造函数
    vector(size_t num = 50) : size(0), capacity(num)
    {
        head = new T[capacity];
    }

    // 析构函数
    ~vector()
    {
        delete[] head;
    }

    // 获取当前元素数量
    size_t getSize() const
    {
        return size;
    }

    // 获取容量
    size_t getCapacity() const
    {
        return capacity;
    }

    // 访问指定位置元素（带边界检查）
    T& at(size_t pos)
    {
        if (pos >= size)
        {
            throw std::out_of_range("vector::at: Index out of range");
        }
        return head[pos];
    }

    // 重载[]运算符（带边界检查）
    T& operator[](size_t index) 
    {
        if (index >= size) 
            throw std::out_of_range("Index out of range");
        return head[index];
    }

    // 在末尾添加元素
    void push_back(const T& value)
    {
        // 如果容量不足，扩容（通常翻倍）
        if (size >= capacity)
        {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        
        head[size++] = value;
    }

    // 移除末尾元素
    void pop_back()
    {
        if (size > 0)
        {
            --size;
            // 对于基本类型，简单减少size即可
            // 对于类类型，可能需要调用析构函数，这里简化处理
        }
        else
        {
            throw std::out_of_range("vector::pop_back: Vector is empty");
        }
    }

    // 清空所有元素
    void clear()
    {
        // 对于类类型，可能需要逐个调用析构函数
        size = 0; // 简单地将size设为0，后续添加元素会覆盖原有数据
    }

    bool empty() const
    {
        return size == 0;
    }



};


#endif