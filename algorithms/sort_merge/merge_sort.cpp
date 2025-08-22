#include <iostream>
#include <vector>

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