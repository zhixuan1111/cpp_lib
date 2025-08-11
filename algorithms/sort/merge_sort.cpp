#include <iostream>
#include <vector>
#include <algorithm>

void mergeArr(std::vector<int>& arr,int l,int m,int r)
{
    int l1=m-l+1;
    int l2=r-m;
}

void mergeSort(std::vector<int>& arr,int l,int r)
{
    if(l<r)
    {
        int m=l+(r-l)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        mergeArr(arr,l,m,r);
    }
    
}

void printArray(const std::vector<int>& arr)
{
    for(auto& i:arr)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
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