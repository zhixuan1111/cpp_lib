# 说明
根据简历中提到的知识点自己实现一番，并且将**相应的知识点**和**常见面试问题**进行总结。主要分为八个部分，算法、容器、C++新特性、设计模式、并发组件、计算机网络、数据库、常用开发工具命令。最后总结成一个综合性的文档，用于面试辅助。
# 一、算法
## 1.1 查找算法：
- 二分查找：✅
- 线性查找：✅
## 1.2 排序算法
- 冒泡排序：✅
- 快速排序：✅
- 归并排序：✅
- 堆排序
## 1.3 二叉树
# 二、容器
## 2.1 vector：✅
### 2.1.1 vector实现方式
1. vector是一个函数模板类，内部由`T* data`，`size_t capacity`，`size_t size`组成，三个参数的含义分别是：
    - `data`：管理`T`类型的一块内存地址，大小为`capacity`；
    - `size`：当前数组中存放的元素个数。
2. 构造函数实现
    - `vector()`：默认构造函数。构造一个空的 vector，不包含任何元素。
    - `vector(size_t size)`：指定大小的构造函数。构造一个包含 n 个元素的 vector，每个元素使用默认值初始化（对于基本类型通常是 0）。
    - `vector(size_t size,T value)`：指定大小和初始值的构造函数。构造一个包含 n 个元素的 vector，每个元素都被初始化为指定值 value。
    - 还有迭代器范围构造函数、拷贝构造函数、移动构造函数（C++11 起）、初始化列表构造函数、分配器构造函数
### 2.1.2 vector相关面试问题
1. `vector`的扩容机制是什么？
    - `vector` 底层使用连续的动态数组存储元素，当现有容量不足以容纳新元素时，会触发扩容
    - 分配一块更大的新内存（通常是当前容量的 1.5~2 倍）
    - 将旧内存中的元素复制 / 移动到新内存
    - 释放旧内存
    - 指向旧内存的迭代器、指针、引用会失效
1. `push_back()`和`emplace_back()`有什么区别？`emplace_back()`是怎么实现的？
    - `push_back()`：
        用于将一个已经构造好的对象复制或移动到容器中。
        如果传入的是临时对象，会先构造临时对象，再通过移动构造函数将其移动到容器（C++11 及以后）；如果传入的是已有对象，则会调用复制构造函数。
    - `emplace_back()`：
        直接在容器的内存空间中原地构造对象，避免了临时对象的创建和移动 / 复制操作。
        它接收的是对象构造函数的参数，而非对象本身，通过这些参数直接在容器末尾构造新元素。
## 2.2 list：✅
## 2.3 哈希表（Hash Table）：✅
哈希表（又称散列表）是一种**基于键值对（Key-Value Pair）存储**的数据结构，其核心优势是通过“哈希函数”将键（Key）映射到存储位置（索引），从而实现**平均O(1)时间复杂度的插入、查找和删除操作**，是计算机科学中效率极高的基础数据结构，广泛应用于缓存、数据库索引、集合去重等场景。

## 2.3.1 哈希表的核心原理
哈希表的工作流程可拆解为“映射-存储-访问”三步，核心依赖**哈希函数**和**解决哈希冲突的策略**两大组件。


### 1. 核心组件1：哈希函数（Hash Function）
哈希函数是哈希表的“灵魂”，其作用是将任意类型、任意长度的“键（Key）”转换为固定范围的“哈希值（Hash Value）”，再通过哈希值计算出该键值对在数组中的**存储索引**。

#### 哈希函数的设计要求
一个优秀的哈希函数需满足以下4个条件，以确保哈希表高效运行：
- **确定性**：同一键（Key）多次输入哈希函数，必须得到相同的哈希值（避免“同一键对应多个位置”的混乱）。
- **高效性**：计算哈希值的过程需快速（时间复杂度O(1)或接近O(1)），避免因函数本身耗时拖慢整体性能。
- **均匀性**：将不同的键尽可能均匀地映射到不同的索引（减少“多个键映射到同一索引”的冲突概率）。
- **范围适配性**：哈希值需能通过取模（如 `Hash Value % 数组长度`）转换为数组的有效索引（0 ≤ 索引 < 数组长度）。

#### 常见哈希函数示例
不同场景下哈希函数的设计不同，以下是3种典型实现：
- **直接定址法**：直接用键（或键的线性变换）作为哈希值，如 `Hash(Key) = a*Key + b`（适用于Key为整数且范围可控的场景，如学生学号映射）。
- **除留余数法**：将键转换为整数后，对数组长度取余，如 `Hash(Key) = (Key的整数表示) % 数组长度`（最常用的方法，需注意数组长度最好为质数，以提升均匀性）。
- **字符串哈希（BKDRHash）**：将字符串的每个字符转换为ASCII码，通过多项式计算哈希值，如 `Hash(String) = s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]`（31是质数，可减少冲突，广泛用于字符串键场景）。
- **DJB2 哈希算法**：通过迭代处理输入字符串的每个字符，不断更新哈希值。

### 2. 核心组件2：解决哈希冲突（Hash Collision）
无论哈希函数设计多么优秀，当键的数量超过数组长度时，**必然会出现“不同键映射到同一索引”的情况**，这就是“哈希冲突”。目前主流的冲突解决策略分为两大类：


#### （1）开放地址法（Open Addressing）
开放地址法的核心是：**冲突发生时，在数组中寻找下一个空闲位置存储键值对**，不依赖额外数据结构。常见实现有3种：
- **线性探测（Linear Probing）**：冲突后，依次检查当前索引的下一个位置（`index+1, index+2, ...`），直到找到空闲位置。  
  优点：实现简单；缺点：容易产生“聚集效应”（多个冲突键连续占用索引，导致后续查找/插入耗时增加）。
- **二次探测（Quadratic Probing）**：冲突后，按“二次方步长”寻找空闲位置（`index+1², index-1², index+2², index-2², ...`）。  
  优点：避免线性探测的聚集效应；缺点：仍可能产生“二次聚集”，且空闲位置查找范围有限。
- **双重哈希（Double Hashing）**：冲突后，用第二个哈希函数计算步长（`step = Hash2(Key)`），按“`index + k*step`”寻找空闲位置（k为探测次数）。  
  优点：步长动态变化，冲突均匀性最好；缺点：需额外设计一个哈希函数，实现稍复杂。


#### （2）链地址法（Chaining）
链地址法的核心是：**将数组的每个索引（称为“桶”，Bucket）作为链表/红黑树的头节点，冲突的键值对直接存储在同一桶的链表/树中**。  
目前主流编程语言（如Java的HashMap、Python的dict）均采用这种方式，具体流程如下：
1. 插入：通过哈希函数计算Key的桶索引，将键值对添加到对应桶的链表/树中；
2. 查找：计算桶索引后，遍历桶内的链表/树，对比Key找到目标值；
3. 删除：同查找流程，找到后从链表/树中删除该键值对。

**优点**：
- 冲突处理简单，无聚集效应；
- 桶内元素动态增长，无需担心数组空间不足；
- 当桶内元素过多时（如Java HashMap中链表长度≥8），可将链表转为红黑树，将查找时间从O(n)优化到O(log n)。

**缺点**：需额外存储链表/树的指针/引用，内存开销略大。


### 3. 动态扩容（Resizing）
哈希表的性能依赖于“负载因子（Load Factor）”——即**已存储键值对数量 / 数组长度**。当负载因子过高（如超过0.7）时，冲突概率会急剧上升，导致操作效率下降。此时需要进行**动态扩容**：
1. 创建一个新的、长度为原数组2倍（通常为2的幂，便于位运算优化）的数组；
2. 遍历原数组的所有桶，将每个键值对重新通过哈希函数映射到新数组的对应桶中（“重哈希，Rehashing”）；
3. 释放原数组内存，将哈希表的引用指向新数组。

**注意**：扩容过程是“一次性耗时操作”（时间复杂度O(n)），但由于扩容频率低（每次扩容后数组长度翻倍），从长期来看，哈希表的平均操作复杂度仍能维持O(1)。

### 4. 简易实现
```cpp
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

size_t hashStringToIndex(const std::string &str, size_t arraySize) {
  // DJB2哈希算法
  unsigned long hash = 5381;
  for (char c : str) {
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }
  // 对数组大小取模，确保结果在有效索引范围内
  return hash % arraySize;
}

class HashTable {
private:
  std::vector<std::list<std::pair<std::string, int>>> table;
  int size; // 哈希表容量

public:
  HashTable(int s);
  ~HashTable();
  void insert(std::string, int);
  void printTable() const;
  int search(std::string) const;
  bool deleteKey(std::string);
  bool resize();
};

HashTable::HashTable(int s = 10) : size(s) { this->table.resize(this->size); }

HashTable::~HashTable() {}

void HashTable::insert(std::string name, int age) {
  int index = hashStringToIndex(name, this->size);
  // 检查该索引下是否已经存在相同的key，若存在的话就更新对应的value
  for (auto &i : this->table[index]) {
    if (i.first == name) {
      i.second = age;
      return;
    }
  }
  // 若不存在，就在当前的list下增加条件键值对
  this->table[index].emplace_back(name, age);
}

void HashTable::printTable() const {
  int temp_index = 0;
  for (auto &list : this->table) {
    std::cout << "[" << temp_index << "]" << " ";
    for (auto &pair : list) {
      std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;
    temp_index++;
  }
}

int HashTable::search(std::string name) const {
  int index = hashStringToIndex(name, this->size);
  // 遍历该链表下的所有值，如果有key等于name，就返回
  auto list = this->table[index];
  for (auto p : list) {
    if (p.first == name) {
      return p.second;
    }
  }
  return -1;
}

bool HashTable::deleteKey(std::string name) {
  int index = hashStringToIndex(name, this->size);
  auto &list = this->table[index];
  for (auto i = list.begin(); i != list.end(); ++i) {
    if ((*i).first == name) {
      list.erase(i);
      return true;
    }
  }
  return false;
}

bool HashTable::resize() {
//   const std::vector<std::list<std::pair<std::string, int>>> old_table =
//       this->table; // 可以不复制，使用std::move转移旧表的所有权
  auto old_table = std::move(this->table); // 更高效，O(1)操作
  this->table.clear();
  this->size = this->size * 2;
  this->table.resize(this->size);

  for (int i = 0; i < old_table.size(); i++) {
    auto &list = old_table[i];
    for (auto &p : list) {
      int temp_index = hashStringToIndex(p.first, this->size);
      //   this->table[temp_index].emplace_back(p);
      this->table[temp_index].emplace_back(std::move(p)); // 更高效
    }
  }
  return true;
}
```


## 2.3.2 哈希表的性能分析
哈希表的性能核心取决于“哈希函数的均匀性”和“冲突解决策略”，以下是不同场景下的时间复杂度对比：

| 操作         | 平均时间复杂度 | 最坏时间复杂度（冲突严重时） | 备注                     |
|--------------|----------------|------------------------------|--------------------------|
| 插入（Insert）| O(1)           | O(n)（链地址法链表过长；开放地址法聚集） | 链地址法红黑树优化后为O(log n) |
| 查找（Search）| O(1)           | O(n)                          | 同上                     |
| 删除（Delete）| O(1)           | O(n)                          | 同上                     |
| 扩容（Resize）| O(n)           | O(n)                          | 一次性操作，频率低       |

**关键结论**：
- 理想情况下（哈希函数均匀、负载因子低），哈希表的插入/查找/删除均为O(1)，是效率最高的数据结构之一；
- 最坏情况下（如哈希函数极差，所有键映射到同一桶），性能会退化为O(n)，但优秀的哈希函数和冲突策略可避免这种情况。


## 2.3.3 哈希表与其他数据结构的对比
为了更清晰理解哈希表的定位，以下对比其与数组、链表、红黑树的核心差异：

| 数据结构   | 插入时间复杂度 | 查找时间复杂度 | 删除时间复杂度 | 核心优势                     | 核心劣势                     |
|------------|----------------|----------------|----------------|------------------------------|------------------------------|
| 哈希表     | 平均O(1)       | 平均O(1)       | 平均O(1)       | 键值映射，操作速度极快       | 无序存储，不支持范围查询     |
| 数组       | O(n)（尾部O(1)）| O(1)（已知索引）| O(n)（尾部O(1)）| 随机访问快，内存连续         | 插入/删除中间元素效率低，长度固定 |
| 链表       | O(1)（已知位置）| O(n)           | O(1)（已知位置）| 插入/删除灵活，内存动态分配   | 随机访问慢，需遍历           |
| 红黑树     | O(log n)       | O(log n)       | O(log n)       | 有序存储，支持范围查询       | 操作复杂度高，平均速度不如哈希表 |


## 2.3.4 常见问题与注意事项
1. **哈希表为什么无序？**  
   因为键的存储位置由哈希函数计算得出，与键的插入顺序无关，因此哈希表无法保证键值对的有序性（若需有序，可使用TreeMap/LinkedHashMap等有序哈希表，本质是哈希表+红黑树/链表维护顺序）。

2. **哈希表的键为什么不能修改？**  
   若键被修改，其哈希值会随之变化，导致原存储位置失效，后续无法通过修改后的键找到对应值。因此，哈希表的键必须是“不可变类型”（如Java的String、Integer，Python的str、int、tuple）。

3. **负载因子的合理值是多少？**  
   主流实现中，负载因子阈值通常设为0.7（如Java HashMap）：低于0.7时，冲突概率低，性能稳定；高于0.7时，冲突概率急剧上升，需触发扩容。

4. **为什么哈希表是空间换时间的操作？**  
    当元素数量接近或超过数组容量时，会触发 “扩容”（如容量翻倍），此时需要申请更大的内存空间。即使元素数量较少，哈希表也需要预先分配一定大小的数组（或动态扩容后保留空闲空间），这些空间可能暂时未被充分利用。

## 2.4 deque

# 三、C++新特性
需要了解的新特性有智能指针、`lambada`表达式
## 3.1 智能指针
### 3.1.1 unique_ptr

`unique_ptr` 是 C++11 引入的智能指针，实现了**独占所有权**语义，用于管理动态分配的内存，确保同一时间只有一个指针拥有对资源的所有权。

#### (1) 核心特性

1. **独占所有权**  
   同一时间只能有一个 `unique_ptr` 指向特定对象，所有权不可共享，这与 `shared_ptr` 的共享所有权形成鲜明对比。

2. **禁止复制操作**  
   - 复制构造函数和复制赋值运算符被显式禁用，防止所有权被复制
   - 错误示例：`unique_ptr<int> p2 = p1;`（编译错误）

3. **支持移动操作**  
   允许通过移动构造函数和移动赋值运算符转移所有权：
   - 移动后，原 `unique_ptr` 会被置为 `nullptr`
   - 示例：`unique_ptr<int> p2 = std::move(p1);`（p1 失去所有权，p2 获得所有权）

#### (2) 实现要点

1. **禁用复制机制**  
   通过 `delete` 关键字显式删除复制构造和复制赋值运算符：
   ```cpp
   unique_ptr(const unique_ptr&) = delete;
   unique_ptr& operator=(const unique_ptr&) = delete;
   ```

2. **实现移动语义**  
   提供移动构造函数和移动赋值运算符，实现所有权的转移：
   ```cpp
   // 移动构造函数
   unique_ptr(unique_ptr&& other) noexcept 
       : ptr(other.ptr) {
       other.ptr = nullptr; // 原指针置空
   }
   
   // 移动赋值运算符
   unique_ptr& operator=(unique_ptr&& other) noexcept {
       if (this != &other) {
           delete ptr;       // 释放当前资源
           ptr = other.ptr;  // 转移所有权
           other.ptr = nullptr; // 原指针置空
       }
       return *this;
   }
   ```

3. **资源管理**  
   - 析构函数自动释放所管理的对象
   - 提供 `reset()` 方法显式释放资源或更换管理的对象
   - 提供 `release()` 方法释放所有权但不释放资源

#### (3) 典型用法

```cpp
// 创建 unique_ptr
std::unique_ptr<int> ptr(new int(42));

// 移动所有权
std::unique_ptr<int> ptr2 = std::move(ptr); // ptr 变为 null

// 管理动态数组
std::unique_ptr<int[]> arr(new int[5]);

// 自定义删除器
auto deleter = [](int* p) { 
    delete p; 
};
std::unique_ptr<int, decltype(deleter)> ptr3(new int(10), deleter);
```

#### (4) 优势总结

- **内存安全**：自动释放资源，避免内存泄漏
- **高性能**：相比 `shared_ptr` 无需维护引用计数，开销更小
- **明确所有权**：清晰表达资源的独占性，使代码意图更明确
- **灵活性**：可用于容器存储，作为函数返回值传递（通过移动语义）

### 3.1.2 shared_ptr
####  (1) 核心特点

`shared_ptr` 是 C++ 标准库提供的智能指针，实现了**共享所有权**机制：
- 多个 `shared_ptr` 可指向同一块动态分配的内存
- 通过**引用计数（reference count）** 跟踪共享该资源的指针数量
- 当最后一个指向资源的 `shared_ptr` 被销毁或重置时，内存会自动释放

####  (2) 实现原理

1. **内部组成**
- `T* ptr`：指向实际管理的对象（原始指针）
- `size_t* ref_count`：指向引用计数的指针，记录当前共享对象的 `shared_ptr` 数量

2. **核心接口**
- 构造函数：`shared_ptr(T *p)`（默认构造）、拷贝构造、移动构造
- 析构函数：`~shared_ptr()`
- 赋值运算符：拷贝赋值、移动赋值
- 访问运算符：`operator*()`（解引用）、`operator->()`
- 辅助方法：`get()`（获取原始指针）、`use_count()`（获取引用计数）、`swap()`（交换内容）

####  (3) 线程安全特性

- **部分线程安全**：
  - 标准库的 `std::shared_ptr` 保证**引用计数的修改是原子操作**（线程安全）
  - **不对管理的对象本身提供线程安全**（`T* ptr` 指向的对象），需要用户自行保证对象的线程安全

- **非线程安全场景**：
  - 简单实现可能不保证引用计数的线程安全
  - 多线程环境下操作同一个 `shared_ptr` 可能导致计数错乱

####  (4) 实现代码示例

```cpp
#include <iostream>
#include <utility> // for std::swap

template <typename T> 
class shared_ptr {
private:
  T* ptr;           // 指向管理的对象
  size_t* ref_count; // 引用计数指针

  // 释放资源
  void release() {
    if (ref_count) {
      (*ref_count)--;
      // 当引用计数为0时，彻底释放资源
      if (*ref_count == 0) {
        delete ptr;
        delete ref_count;
      }
      // 清空当前实例的指针
      ptr = nullptr;
      ref_count = nullptr;
    }
  }

public:
  // 构造函数：从原始指针构造
  explicit shared_ptr(T* p = nullptr) : ptr(p), ref_count(nullptr) {
    if (p) {
      ref_count = new size_t(1); // 初始化引用计数为1
    }
  }

  // 拷贝构造函数
  shared_ptr(const shared_ptr& other) 
      : ptr(other.ptr), ref_count(other.ref_count) {
    if (ref_count) { // 防止拷贝空对象
      (*ref_count)++;
    }
  }

  // 移动构造函数
  shared_ptr(shared_ptr&& other) noexcept 
      : ptr(other.ptr), ref_count(other.ref_count) {
    // 转移所有权后将源对象指针置空
    other.ptr = nullptr;
    other.ref_count = nullptr;
  }

  // 析构函数
  ~shared_ptr() {
    release();
  }

  // 拷贝赋值运算符
  shared_ptr& operator=(const shared_ptr& other) {
    // 防止自赋值
    if (this != &other) {
      // 先释放当前资源
      release();
      // 拷贝新资源
      ptr = other.ptr;
      ref_count = other.ref_count;
      if (ref_count) {
        (*ref_count)++;
      }
    }
    return *this;
  }

  // 移动赋值运算符
  shared_ptr& operator=(shared_ptr&& other) noexcept {
    if (this != &other) {
      // 释放当前资源
      release();
      // 转移所有权
      ptr = other.ptr;
      ref_count = other.ref_count;
      // 源对象指针置空
      other.ptr = nullptr;
      other.ref_count = nullptr;
    }
    return *this;
  }

  // 重载解引用运算符
  T& operator*() const {
    return *ptr;
  }

  // 重载->运算符
  T* operator->() const {
    return ptr;
  }

  // 获取原始指针
  T* get() const {
    return ptr;
  }

  // 获取当前引用计数
  size_t use_count() const {
    return ref_count ? *ref_count : 0;
  }

  // 交换两个shared_ptr的内容
  void swap(shared_ptr& other) {
    std::swap(ptr, other.ptr);
    std::swap(ref_count, other.ref_count);
  }
};

// 辅助函数：创建shared_ptr（类似std::make_shared）
template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
  return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
```

####  (5) make_shared 相关知识点

`make_shared` 是创建 `shared_ptr` 的推荐方式，具有以下优势：

1. **内存分配更高效**：
   - 传统方式（`new` + `shared_ptr`）：需要两次内存分配（对象本身 + 引用计数）
   - `make_shared` 方式：一次性分配连续内存，同时存储对象和引用计数（包括控制信息），减少内存分配开销

2. **提高异常安全性**：
   - 在将指针作为参数传递等场景下，避免因异常抛出导致的内存泄漏风险
   - 例如：`func(shared_ptr<T>(new T), other_func())` 可能因函数参数求值顺序导致内存泄漏，而 `func(make_shared<T>(), other_func())` 可避免此问题

3. **简化代码**：
   - 无需显式使用 `new` 操作符
   - 语法：`make_shared<类型>(构造参数)`，使代码更简洁直观

### 3.1.3 weak_ptr

`weak_ptr` 是 C++ 智能指针库中的重要组成部分，主要用于解决 `shared_ptr` 可能导致的循环引用问题。它本身不拥有对象的所有权，仅作为 `shared_ptr` 的观察者存在，持有被观察对象的弱引用，不会影响被观察者的生命周期。

#### (1) 主要特性

1. **不控制对象生命周期**  
   `weak_ptr` 不会增加所指向对象的引用计数，当最后一个 `shared_ptr` 被销毁时，即使有 `weak_ptr` 指向该对象，对象也会被释放。

2. **解决循环引用**  
   当两个对象互相持有 `shared_ptr` 时会形成循环引用，导致引用计数无法归零，引发内存泄漏。使用 `weak_ptr` 替代其中一个 `shared_ptr` 可打破这种循环。

3. **需转换为 `shared_ptr` 才能访问对象**  
   `weak_ptr` 本身不能直接访问对象，必须通过 `lock()` 方法转换为 `shared_ptr`，这确保了在访问时对象仍然存在。

#### (2) 实现原理

##### 控制块（Control Block）

`weak_ptr` 与 `shared_ptr` 共享同一个控制块来管理对象生命周期，控制块包含以下核心信息：
- **强引用计数（strong count）**：跟踪持有对象所有权的 `shared_ptr` 数量，当减为 0 时对象被销毁。
- **弱引用计数（weak count）**：跟踪观察对象的 `weak_ptr` 数量（包括控制块自身的引用），当减为 0 时控制块被销毁。
- 指向对象的指针、删除器（deleter）和分配器（allocator）。

##### 核心机制

1. **初始化与关联**  
   当 `weak_ptr` 从 `shared_ptr` 初始化或赋值时，会指向其控制块并将弱引用计数 +1，但不影响强引用计数。

2. **对象访问机制**  
   通过 `lock()` 方法转换为 `shared_ptr` 才能访问对象：
   - 检查强引用计数是否 > 0（对象是否存活）。
   - 若存活，返回新的 `shared_ptr` 并将强引用计数 +1，确保访问期间对象不被销毁。
   - 若已销毁，返回空的 `shared_ptr`。

3. **生命周期管理**  
   - 最后一个 `shared_ptr` 销毁时（强引用计数 = 0），对象被销毁，但控制块保留（可能还有 `weak_ptr` 引用）。
   - 最后一个 `weak_ptr` 销毁时（弱引用计数 = 0），控制块被释放，彻底清理内存。

4. **循环引用解决原理**  
   在循环引用场景中，`weak_ptr` 仅增加弱引用计数，不影响强引用计数。当外部 `shared_ptr` 销毁时，强引用计数可正常减为 0，对象被销毁，打破循环。

#### (3) 简化实现示例

```cpp
// 控制块结构（简化版）
template <typename T>
struct ControlBlock {
    int strong_count;  // 强引用计数
    int weak_count;    // 弱引用计数
    T* object;         // 指向实际对象
    // ... 其他成员（删除器等）
};

// weak_ptr 简化实现
template <typename T>
class weak_ptr {
private:
    ControlBlock<T>* cb;  // 指向控制块

public:
    // 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& sp) : cb(sp.cb) {
        if (cb) cb->weak_count++;  // 弱引用计数+1
    }

    // 转换为 shared_ptr（lock() 方法）
    shared_ptr<T> lock() const {
        if (cb && cb->strong_count > 0) {
            // 对象存活，返回 shared_ptr 并增加强引用计数
            return shared_ptr<T>(cb);
        }
        return shared_ptr<T>();  // 对象已销毁，返回空
    }

    // 析构函数
    ~weak_ptr() {
        if (cb) {
            cb->weak_count--;
            if (cb->weak_count == 0 && cb->strong_count == 0) {
                delete cb;  // 弱引用计数为0且对象已销毁，释放控制块
            }
        }
    }
};
```

## 3.2 `lambada`表达式

# 四、设计模式
## 4.1 单例模式：✅

单例模式（Singleton Pattern）是一种创建型设计模式，核心目标是确保**一个类在整个程序生命周期中仅存在一个实例**，并提供一个全局唯一的访问点，避免频繁创建销毁对象带来的资源开销，同时保证实例的全局可访问性。


### 4.1.1、核心实现方式：局部静态变量懒汉式（推荐）
该实现方式是 C++11 及以上标准中最简洁、安全的单例实现之一，兼具懒加载（Lazy Initialization）和线程安全特性。

#### (1) 实现核心步骤
- **私有化构造相关函数**：杜绝外部通过构造、拷贝、赋值创建新实例，确保实例唯一性。
  - 私有化默认构造函数：防止外部直接 `new Singleton()` 创建对象。
  - 删除拷贝构造函数：防止外部通过拷贝（如 `Singleton s = Singleton::getInstance()`）创建新实例。
  - 删除复制赋值运算符：防止外部通过赋值（如 `Singleton s1; s1 = Singleton::getInstance()`）创建新实例。
- **提供全局访问点**：通过静态成员函数 `getInstance()` 控制实例的创建与访问，内部使用**局部静态变量**存储唯一实例，确保仅初始化一次。

#### (2) 代码实现
```cpp
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
```

#### (3) 调用方式
```cpp
// 全局唯一访问方式：通过静态函数获取实例，无需手动创建
Singleton& instance = Singleton::getInstance();
instance.doSomething(); // 调用实例的成员函数
```


### 4.1.2 关键注意事项
#### (1) 静态成员变量的初始化规则
若采用「返回指针」而非「返回引用」的实现方式（如传统懒汉式），需在**类内声明静态成员指针**，并在**类外全局作用域初始化**（避免未初始化的野指针问题）。

示例（返回指针的传统实现，需额外注意线程安全）：
```cpp
class Singleton {
private:
    // 类内声明静态成员指针（存储实例地址）
    static Singleton* instance;

    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        // 注意：此代码在 C++11 前非线程安全（需手动加锁）
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

// 类外初始化静态成员指针（必须！否则链接时会报错）
Singleton* Singleton::instance = nullptr;
```

#### (2) 静态成员函数的访问规则
- 静态成员函数（如 `getInstance()`）**不属于任何类实例**，没有 `this` 指针，因此默认只能访问「静态成员变量/函数」。
- 若需在静态函数中操作「非静态成员」，需显式传入类实例（如通过 `getInstance()` 获取实例后调用非静态成员）。


### 4.1.3 线程安全深度解析
单例模式的线程安全核心在于**避免多线程同时初始化实例导致的「重复创建」问题**，不同实现方式的线程安全性差异较大，需结合 C++ 标准版本判断。

#### (1) 局部静态变量懒汉式（本文核心实现）
- **C++11 及以上**：**线程安全**。  
  C++11 标准明确规定：「局部静态变量的初始化会在首次访问时进行，且编译器会自动插入同步锁（如 `std::mutex`），确保即使多线程同时调用 `getInstance()`，也只会初始化一次实例」。
- **C++11 以下**：**非线程安全**。  
  旧标准未规定局部静态变量的初始化同步机制，多线程同时进入 `getInstance()` 可能触发多次 `instance` 初始化，导致内存泄漏或实例不唯一。

#### (2) 其他实现方式的线程安全性
| 实现方式       | 核心逻辑                                  | 线程安全性（C++11+） | 优缺点                                  |
|----------------|-------------------------------------------|----------------------|-----------------------------------------|
| 饿汉式（指针） | 程序启动时初始化静态指针（`static Singleton* instance = new Singleton();`） | 安全                 | 优点：无需锁，效率高；缺点：提前占用内存，无法懒加载 |
| 传统懒汉式（指针） | 首次调用时判断 `instance == nullptr` 后初始化 | 非安全（需手动加锁） | 优点：懒加载；缺点：需手动实现锁机制，易出现死锁或性能问题 |

##### 传统懒汉式的线程安全优化（手动加锁）
若需在 C++11 以下环境使用懒汉式，需通过互斥锁（`std::mutex`）保证初始化唯一：
```cpp
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx; // 互斥锁，保护实例初始化

    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        // 双重检查锁定（Double-Checked Locking）：减少锁竞争开销
        if (instance == nullptr) { // 第一次检查：无锁，快速判断是否已初始化
            std::lock_guard<std::mutex> lock(mtx); // 加锁
            if (instance == nullptr) { // 第二次检查：防止多线程等待锁后重复初始化
                instance = new Singleton();
            }
        }
        return instance;
    }
};

// 类外初始化静态成员
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;
```

#### (3) 注意：实例创建安全 ≠ 成员访问安全
即使实例的创建过程是线程安全的，**多线程对实例的「非静态成员变量/函数」的并发操作仍可能引发数据竞争**（如多个线程同时调用 `instance->modifyData()` 修改同一成员变量）。

解决方案：
- 对非静态成员的读写操作加锁（如 `std::mutex`）。
- 使用线程安全的数据结构（如 `std::atomic` 修饰成员变量）。

# 五、并发组件
## 5.1 线程池
# 六、计算机网络
需要熟悉`HTTP`,`TCP`,`UDP`,`IP`等协议以及收集面试中常见的问题，对于`TCP`,`UDP`还要知道他们的编程实现。对于`OSI`中的应用层、传输层、网络层等其他知识也需要了解
## 6.1 UDP
## 6.2 TCP
## 6.3 HTTP
## 6.4 IP

# 七、数据库(SQLite)
学会SQL数据库常见的增删查改操作

## 7.1 增（INSERT）操作

用于向表中插入一条或多条记录。
```sql
INSERT INTO 表名 (列1, 列2, ...) VALUES (值1, 值2, ...);
```
以下示例向 users 表中插入了一条记录，名字为 "Alice"，年龄为 30。
```sql
INSERT INTO users (name, age) VALUES ('Alice', 30);
```
## 7.2 查（SELECT）操作
用于从表中查询数据。

```sql
SELECT 列1, 列2, ... FROM 表名 WHERE 条件;
```
该查询从 `users` 表中选择所有年龄大于 25 的用户的名字和年龄。
```sql
复制代码
SELECT name, age FROM users WHERE age > 25;
```

## 7.3 改（UPDATE）操作
用于更新表中已存在的记录。
```sql
UPDATE 表名 SET 列1 = 值1, 列2 = 值2, ... WHERE 条件;
```
将 users 表中名为 "Alice" 的用户的年龄更新为 31。
```sql
UPDATE users SET age = 31 WHERE name = 'Alice';
```

## 7.4 删（DELETE）操作
用于从表中删除记录。
```sql
DELETE FROM 表名 WHERE 条件;
```
该语句将从 users 表中删除名为 "Alice" 的用户记录。
```sql
DELETE FROM users WHERE name = 'Alice';
```

# 八、常见开发工具的命令
## 8.1 Linux常用命令
## 8.2 git常用命令
### 8.2.1 git init
初始化新的 Git 仓库
- 常用参数/用法
    - `git init`：在当前目录创建一个新的、空的 Git 仓库
    - `git init /path/to/your/project`：在`/path/to/your/project`创建一个新的、空的 Git 仓库
    - `git init -b main`：初始化仓库，并设置默认分支为 'main'
    - `git init --bare /srv/my-project.git`：创建裸仓库，保证团队协作和自动化流程的可靠性与一致性。
### 8.2.1 git add
将文件添加到暂存区
- 基本用法：`git add <文件/目录>`
- 常用参数 / 用法：
    - `git add .`：添加**当前目录**所有修改到暂存区
    - `git add --all` 或 `-A`：添加**整个 Git 仓库中**所有的修改到暂存区
    - `git add -u`：只添加已跟踪文件的修改和删除（不包括新增文件）
    - `git add src/`：添加整个目录的修改
    - `git add README.md`：添加单个文件
## 8.3 Cmake常用命令