#include <iostream>
#include <cassert>
#include "vector.h"  // 包含你的vector头文件

// 测试默认构造函数和基本功能
void test_basic_functions() {
    std::cout << "Testing basic functions...";
    
    vector<int> v;
    assert(v.empty() == true);
    assert(v.size() == 0);
    
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    assert(v.empty() == false);
    assert(v.size() == 3);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v.front() == 1);
    assert(v.back() == 3);
    
    v.pop_back();
    assert(v.size() == 2);
    assert(v.back() == 2);
    
    v.clear();
    assert(v.empty() == true);
    assert(v.size() == 0);
    
    std::cout << "Passed!\n";
}

// 测试带参数的构造函数和迭代器
void test_constructors_and_iterators() {
    std::cout << "Testing constructors and iterators...";
    
    // 测试填充构造函数
    vector<int> v(5, 10);
    assert(v.size() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(v[i] == 10);
    }
    
    // 测试迭代器构造函数
    int arr[] = {1, 2, 3, 4, 5};
    vector<int> v2(arr, arr + 5);
    assert(v2.size() == 5);
    
    // 测试迭代器遍历
    int count = 1;
    for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
        assert(*it == count++);
    }
    
    // 测试const迭代器
    const vector<int>& cv = v2;
    count = 1;
    for (vector<int>::const_iterator it = cv.begin(); it != cv.end(); ++it) {
        assert(*it == count++);
    }
    
    std::cout << "Passed!\n";
}

// 测试插入和删除
void test_insert_and_erase() {
    std::cout << "Testing insert and erase...";
    
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    // 在位置1插入元素10
    v.insert(v.begin() + 1, 10);
    assert(v.size() == 4);
    assert(v[0] == 1);
    assert(v[1] == 10);
    assert(v[2] == 2);
    assert(v[3] == 3);
    
    // 删除位置1的元素
    v.erase(v.begin() + 1);
    assert(v.size() == 3);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    
    // 测试范围插入
    int arr[] = {4, 5, 6};
    v.insert(v.end(), arr, arr + 3);
    assert(v.size() == 6);
    assert(v[3] == 4);
    assert(v[4] == 5);
    assert(v[5] == 6);
    
    // 测试范围删除
    v.erase(v.begin() + 3, v.end());
    assert(v.size() == 3);
    
    std::cout << "Passed!\n";
}

// 测试拷贝构造和赋值
void test_copy_and_assignment() {
    std::cout << "Testing copy and assignment...";
    
    vector<int> v;
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    
    // 测试拷贝构造
    vector<int> v2(v);
    assert(v2.size() == v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        assert(v2[i] == v[i]);
    }
    
    // 测试赋值运算符
    vector<int> v3;
    v3 = v;
    assert(v3.size() == v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        assert(v3[i] == v[i]);
    }
    
    // 测试自赋值
    v3 = v3;
    assert(v3.size() == v.size());
    
    std::cout << "Passed!\n";
}

// 测试移动操作（如果实现了C++11及以上特性）
void test_move_operations() {
    std::cout << "Testing move operations...";
    
    vector<int> v;
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    size_t old_size = v.size();
    
    // 测试移动构造
    vector<int> v2(std::move(v));
    assert(v2.size() == old_size);
    assert(v.size() == 0);  // 原vector应该为空
    
    // 测试移动赋值
    vector<int> v3;
    v3 = std::move(v2);
    assert(v3.size() == old_size);
    assert(v2.size() == 0);  // 被移动的vector应该为空
    
    std::cout << "Passed!\n";
}

// 测试边界情况
void test_edge_cases() {
    std::cout << "Testing edge cases...";
    
    // 测试空vector的操作
    vector<int> v;
    assert(v.begin() == v.end());
    // 以下操作应保证不崩溃
    v.clear();
    v.pop_back();  // 对空vector调用pop_back()应安全
    
    // 测试大量元素插入，检查内存管理
    vector<int> v2;
    for (int i = 0; i < 10000; ++i) {
        v2.push_back(i);
    }
    assert(v2.size() == 10000);
    for (int i = 0; i < 10000; ++i) {
        assert(v2[i] == i);
    }
    
    // 测试迭代器在修改后的有效性
    v2.push_back(10000);
    vector<int>::iterator it = v2.begin() + 5000;
    assert(*it == 5000);
    
    std::cout << "Passed!\n";
}

int main() {
    test_basic_functions();
    test_constructors_and_iterators();
    test_insert_and_erase();
    test_copy_and_assignment();
    
    // 如果你的vector实现了移动语义，取消下面这行注释
    // test_move_operations();
    
    test_edge_cases();
    
    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
