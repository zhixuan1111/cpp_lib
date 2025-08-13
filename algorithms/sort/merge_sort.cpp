#include <iostream>
#include <vector>
#include <algorithm>

//合并数组的函数
void mergeArr(std::vector<int> &arr, int l, int m, int r) {
  int l1 = m - l + 1;
  int l2 = r - m;

  std::vector<int> leftArr(l1), rightArr(l2);
  for (int i = 0; i < l1; i++) {
    leftArr[i] = arr[l + i];
  }
  for (int j = 0; j < l2; j++) {
    rightArr[j] = arr[m + 1 + j];
  }

  int i = 0;
  int j = 0;
  while (i < l1 && j < l2) {
    if (leftArr[i] < rightArr[j]) {
      arr[l] = leftArr[i];
      i++;
    } else {
      arr[l] = rightArr[j];
      j++;
    }
    l++;
  } // l1或者l2被遍历完跳出循环

  while (i < l1) {
    arr[l] = leftArr[i];
    i++;
    l++;
  }
  while (j < l2) {
    arr[l] = rightArr[j];
    j++;
    l++;
  }
}

void mergeSort(std::vector<int> &arr, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    mergeArr(arr, l, m, r);
  }
}

void printArray(const std::vector<int> &arr) {
  for (auto &i : arr) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> arr = {12, 11, 13, 5, 6, 7};
  std::cout << "before sort: ";
  printArray(arr);

  mergeSort(arr, 0, arr.size() - 1);

  std::cout << "after sort: ";
  printArray(arr);

  return 0;
}