#include <iostream>
#include <vector>

// 可以扩展到三路分区
int partition(std::vector<int> &arr, int low, int high) {
  int pivot = arr[high]; //  设置最后的为基准值
  int i = low - 1;       // 小于基准值的数据的最大索引
  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      std::swap(arr[j], arr[i]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i +
         1; // 本轮已经将小于基准值的元素移动到索引i及i以前的位置，再将基准值交换到i+1处即可
}

void quickSort(std::vector<int> &arr, int low, int high) {

  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void printArray(const std::vector<int> &arr) {
  for (int num : arr) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> arr = {10, 7, 8, 9, 1, 5};
  int n = arr.size();

  std::cout << "before sort: ";
  printArray(arr);
  quickSort(arr, 0, n - 1);
  std::cout << "after sort: ";
  printArray(arr);

  return 0;
}
