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
## 八股
1. `push_back()`和`emplace_back()`有什么区别？`emplace_back()`是怎么实现的？
    - `push_back()`：
        用于将一个已经构造好的对象复制或移动到容器中。
        如果传入的是临时对象，会先构造临时对象，再通过移动构造函数将其移动到容器（C++11 及以后）；如果传入的是已有对象，则会调用复制构造函数。
    - `emplace_back()`：
        直接在容器的内存空间中原地构造对象，避免了临时对象的创建和移动 / 复制操作。
        它接收的是对象构造函数的参数，而非对象本身，通过这些参数直接在容器末尾构造新元素。
    - 代码实现
        ```cpp
        template <typename... Args>
        void emplace_back(Args&&... args) {
        // 确保有足够内存
        if (size_ == capacity_) {
            reallocate();  // 扩容
        }
        // 获取新元素的内存地址
        T* p = data_ + size_;
        // 原地构造对象（placement new）
        new (p) T(std::forward<Args>(args)...);  // 转发参数到构造函数
        size_++;
        }
        ```
