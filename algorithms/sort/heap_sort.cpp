#include <iostream>
#include <vector>

using namespace std;

// 将以 root 为根的子树调整为最大堆
void heapify(vector<int>& arr, int n, int root) 
{
    int largest = root;        // 初始化最大值为根节点
    int left = 2 * root + 1;   // 左子节点
    int right = 2 * root + 2;  // 右子节点

    // 如果左子节点比根节点大
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点比当前最大值还大
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点
    if (largest != root) 
    {
        swap(arr[root], arr[largest]);     // 交换
        heapify(arr, n, largest);          // 递归调整受影响的子树
    }
}

// 主堆排序函数
void heapSort(vector<int>& arr) 
{
    int n = arr.size();

    // 建堆（重新排列数组）
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 一个个取出元素放到末尾
    for (int i = n - 1; i > 0; i--) 
    {
        swap(arr[0], arr[i]);        // 把当前最大值放到末尾
        heapify(arr, i, 0);          // 对剩余元素重新构建堆
    }
}

// 打印数组
void printArray(const vector<int>& arr) 
{
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// 主函数测试
int main() 
{
    vector<int> arr = {12, 11, 13, 5, 6, 7};

    cout << "orignal:\n";
    printArray(arr);

    heapSort(arr);

    cout << "after sort:\n";
    printArray(arr);

    return 0;
}
