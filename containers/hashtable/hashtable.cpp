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

int main() {
  std::cout << "nihao!" << std::endl;
  HashTable a;
  a.insert("zhangsan", 11);
  a.insert("lisi", 25);
  a.insert("maliu", 30);
  a.printTable();
  // a.deleteKey("maliu");
  // a.printTable();

  std::cout << "---after resize---" << std::endl;
  a.resize();
  a.printTable();

  // std::cout<<"maliu -> "<<a.search("maliu")<<std::endl;

  // std::list<int> a;
  // a.push_back(1);
  // a.push_back(2);
  // a.push_back(3);
  // a.emplace_back(1);
  // a.emplace_back(2);

  // for (auto& i:a)
  // {
  //     /* code */
  //     std::cout<<i<<" "<<std::endl;
  // }
  // a.erase(a.begin());

  // for (auto& i:a)
  // {
  //     /* code */
  //     std::cout<<i<<" "<<std::endl;
  // }

  return 0;
}