# 哈希表（Hash Table）全面解析
哈希表（又称散列表）是一种**基于键值对（Key-Value Pair）存储**的数据结构，其核心优势是通过“哈希函数”将键（Key）映射到存储位置（索引），从而实现**平均O(1)时间复杂度的插入、查找和删除操作**，是计算机科学中效率极高的基础数据结构，广泛应用于缓存、数据库索引、集合去重等场景。

## 一、哈希表的核心原理
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


## 二、哈希表的性能分析
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


## 三、哈希表与其他数据结构的对比
为了更清晰理解哈希表的定位，以下对比其与数组、链表、红黑树的核心差异：

| 数据结构   | 插入时间复杂度 | 查找时间复杂度 | 删除时间复杂度 | 核心优势                     | 核心劣势                     |
|------------|----------------|----------------|----------------|------------------------------|------------------------------|
| 哈希表     | 平均O(1)       | 平均O(1)       | 平均O(1)       | 键值映射，操作速度极快       | 无序存储，不支持范围查询     |
| 数组       | O(n)（尾部O(1)）| O(1)（已知索引）| O(n)（尾部O(1)）| 随机访问快，内存连续         | 插入/删除中间元素效率低，长度固定 |
| 链表       | O(1)（已知位置）| O(n)           | O(1)（已知位置）| 插入/删除灵活，内存动态分配   | 随机访问慢，需遍历           |
| 红黑树     | O(log n)       | O(log n)       | O(log n)       | 有序存储，支持范围查询       | 操作复杂度高，平均速度不如哈希表 |


## 四、常见问题与注意事项
1. **哈希表为什么无序？**  
   因为键的存储位置由哈希函数计算得出，与键的插入顺序无关，因此哈希表无法保证键值对的有序性（若需有序，可使用TreeMap/LinkedHashMap等有序哈希表，本质是哈希表+红黑树/链表维护顺序）。

2. **哈希表的键为什么不能修改？**  
   若键被修改，其哈希值会随之变化，导致原存储位置失效，后续无法通过修改后的键找到对应值。因此，哈希表的键必须是“不可变类型”（如Java的String、Integer，Python的str、int、tuple）。

3. **负载因子的合理值是多少？**  
   主流实现中，负载因子阈值通常设为0.7（如Java HashMap）：低于0.7时，冲突概率低，性能稳定；高于0.7时，冲突概率急剧上升，需触发扩容。

4. **为什么哈希表是空间换时间的操作？**  
    当元素数量接近或超过数组容量时，会触发 “扩容”（如容量翻倍），此时需要申请更大的内存空间。即使元素数量较少，哈希表也需要预先分配一定大小的数组（或动态扩容后保留空闲空间），这些空间可能暂时未被充分利用。