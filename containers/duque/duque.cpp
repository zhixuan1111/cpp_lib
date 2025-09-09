#include <cassert>
#include <cstring>
#include <iostream>

template <typename T> class MyDeque {
private:
  static const int BUFFER_SIZE = 4; // 每个缓冲区最多存几个元素
  static const int INITIAL_MAP_SIZE = 8;  // map管理的内存个数

  T **map;         // map 控制多个缓冲区
  int mapSize;     // map 长度
  int startIdx;    // 起始缓冲区索引
  int startOffset; // 起始缓冲区内偏移
  int endIdx;      // 结束缓冲区索引
  int endOffset;   // 结束缓冲区内偏移

  int count; // 元素个数

  // 为指定索引的缓冲区分配内存（仅当该缓冲区未分配时）
  void allocateBuffer(int index) {
    if (map[index] == nullptr) {
      map[index] = new T[BUFFER_SIZE];
    }
  }

  // 当从队列头部（push_front）添加元素时，检查 map 是否有足够空间，若不足则扩容。
  // 预防性扩容
  void expandMapIfNeededFront() {
    if (startIdx == 0) {
      int newSize = mapSize * 2;
      T **newMap = new T *[newSize];
      std::memset(newMap, 0, sizeof(T *) * newSize);
      int newStart = newSize / 4;
      // 新 map 中，原缓冲区的前、后方各有 4 个空位，留给未来 push_front() 扩展。

      for (int i = 0; i < mapSize; ++i) {
        newMap[newStart + i] = map[i];
      }
      delete[] map;
      startIdx += newStart;
      endIdx += newStart;
      mapSize = newSize;
      map = newMap;
    }
  }

  void expandMapIfNeededBack() {
    if (endIdx == mapSize - 1) {
      int newSize = mapSize * 2;
      T **newMap = new T *[newSize];
      std::memset(newMap, 0, sizeof(T *) * newSize);
      int newStart = newSize / 4;

      for (int i = 0; i < mapSize; ++i) {
        newMap[newStart + i] = map[i];
      }
      delete[] map;
      startIdx += newStart;
      endIdx += newStart;
      mapSize = newSize;
      map = newMap;
    }
  }

public:
  MyDeque() {
    mapSize = INITIAL_MAP_SIZE;
    map = new T *[mapSize];
    std::memset(map, 0, sizeof(T *) * mapSize);

    int center = mapSize / 2;
    startIdx = endIdx = center;
    startOffset = endOffset = 0;
    allocateBuffer(center);

    count = 0;
  }

  ~MyDeque() {
    for (int i = 0; i < mapSize; ++i) {
      delete[] map[i];
    }
    delete[] map;
  }

  void push_back(const T &val) {
    expandMapIfNeededBack();
    allocateBuffer(endIdx);
    map[endIdx][endOffset++] = val;
    if (endOffset == BUFFER_SIZE) {
      endOffset = 0;
      endIdx++;
    }
    count++;
  }

  void push_front(const T &val) {
    expandMapIfNeededFront();
    if (startOffset == 0) {
      startIdx--;
      allocateBuffer(startIdx);
      startOffset = BUFFER_SIZE;
    }
    map[startIdx][--startOffset] = val;
    count++;
  }

  T &operator[](int index) {
    assert(index >= 0 && index < count);
    int offset = startOffset + index;
    int bufIdx = startIdx + offset / BUFFER_SIZE;
    int innerIdx = offset % BUFFER_SIZE;
    return map[bufIdx][innerIdx];
  }

  int size() const { return count; }
};

int main() {
  MyDeque<int> arr;
  arr.push_back(1);

  return 0;
}