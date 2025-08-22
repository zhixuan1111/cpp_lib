# 归并排序知识点
## 归并排序实现方法
归并排序是典型的分治算法，主要通过 "分解 - 合并" 两个步骤实现排序。由两个函数组成，分别是`mergeSort()`和`mergeArr()`。
1. 分解：
    - 递归调用`mergeSort()`将待排序数组不断二分，直到每个子数组只包含一个元素（单个元素默认有序）。
    - 例如，数组 [38, 27, 43, 3, 9, 82, 10] 会被分解为 [38]、[27]、[43]、[3]、[9]、[82]、[10]。
2. 合并：
    - 从最小的子数组开始，两两合并为一个有序数组。
    - 合并时需创建临时数组，比较两个子数组的元素，按从小到大顺序依次放入临时数组，最后将临时数组复制回原数组。
    - 重复合并过程，直到所有子数组合并为一个完整的有序数组。
## 归并排序性能特点
1. 时间复杂度稳定为 **O (n log n)**（最好、最坏、平均情况一致）
2. 空间复杂度为 **O (n)**（需要额外空间存储合并结果）
3. 是稳定排序（相等元素的相对顺序保持不变）
## 归并排序代码实现
```cpp
void mergeArr(std::vector<int>& arr,int l,int m,int r)
{
    int l1=m-l+1;
    int l2=r-m;
    std::vector<int> leftArr(l1),rightArr(l2);
    //赋值
    for(int i=0;i<l1;i++){
        leftArr[i]=arr[l+i];
    }
    for(int j=0;j<l2;j++){
        rightArr[j]=arr[m+j+1];
    }
    int i=0;
    int j=0;
    while (i<l1&&j<l2){
        if(leftArr[i]>rightArr[j]){
            arr[l]=rightArr[j];
            j++;
            l++;
        }else{
            arr[l]=leftArr[i];
            i++;
            l++;
        }
    }   //当有一个子数组遍历完后就退出

    while (i<l1){
        arr[l]=leftArr[i];
        i++;
        l++;
    }
    while(j<l2){
        arr[l]=rightArr[j];
        j++;
        l++;
    } 
}

void mergeSort(std::vector<int>& arr,int l,int r){
    if(l<r){
        int m=l+(r-l)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        mergeArr(arr,l,m,r);
    } 
}
```