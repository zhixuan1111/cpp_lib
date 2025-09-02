# 堆排序代码实现

回到[主目录 堆排序](../../README.md#124-堆排序)  

```cpp
// 堆化操作：确保以index为根的子树满足最大堆性质
void heapify(std::vector<int> &arr, int n, int index) {
  int largest = index;       // 根节点
  int left = 2 * index + 1;  // 左子节点
  int right = 2 * index + 2; // 右子节点

  // 如果左子节点大于根节点
  if (left < n && arr[left] > arr[largest]) {
    largest = left;
  }

  // 如果右子节点大于当前最大值
  if (right < n && arr[right] > arr[largest]) {
    largest = right;
  }

  // 如果最大值不是根节点，则交换并递归堆化
  if (largest != index) {
    std::swap(arr[index], arr[largest]);
    heapify(arr, n, largest);
    // 终止条件：如果与左子节点交换，递归处理左子树（此时左子树可能因交换被破坏了堆性质）让他左子树符合大根堆
  }
}

// 堆排序函数
void heapSort(std::vector<int> &arr) {
  int n = arr.size();

  // 从最后一个非叶子节点开始调整(按照最大堆的属性调整)一直往前 到根节点
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i);
  }

  // 从堆中提取元素
  for (int i = n - 1; i > 0; i--) {
    // 将当前根节点（最大值）移到数组末尾
    std::swap(arr[0], arr[i]);

    // 此时可能不是大根堆，所以需对剩余元素重新堆化
    heapify(arr, i, 0);
  }
}
```

回到[主目录 堆排序](../../README.md#124-堆排序)  