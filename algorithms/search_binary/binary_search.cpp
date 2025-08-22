#include <iostream>
#include <vector>

// 二分查找函数：返回target在数组中的索引，找不到返回-1
int binarySearch(const std::vector<int> &nums, int target) {
  int left = 0;                // 左边界
  int right = nums.size() - 1; // 右边界

  while (left <= right) {
    int mid = left + (right - left) / 2; // 防止溢出

    if (nums[mid] == target) {
      return mid; // 找到目标
    } else if (nums[mid] < target) {
      left = mid + 1; // 在右边找
    } else {
      right = mid - 1; // 在左边找
    }
  }

  return -1; // 没找到
}

int main() {
  std::vector<int> nums = {1, 3, 5, 7, 9, 11, 13}; // 必须是有序数组
  int target = 7;

  int index = binarySearch(nums, target);

  if (index != -1) {
    std::cout << "找到了，索引是: " << index << std::endl;
  } else {
    std::cout << "未找到目标元素。" << std::endl;
  }

  return 0;
}
