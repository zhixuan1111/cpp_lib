# vector
## 实现方式
1. vector是一个函数模板类，内部由`T* data`，`size_t capacity`，`size_t size`组成，三个参数的含义分别是：
    - `data`：管理`T`类型的一块内存地址，大小为`capacity`；
    - `size`：当前数组中存放的元素个数。
2. 构造函数实现
    ```cpp
    vector(size_t num = 50) : size(0), capacity(num) {
        data = new T[capacity]; 
    }
    ```
3. 析构函数实现
    ```cpp
    ~vector() {
        delete[] head; 
    }
    ```
