#include <iostream>
#include "Standard.h"

struct records{
    KeyType key;
};
typedef records List[maxsize];

void sort(int n, List &A){
    int begin = 0;  //将记录序列的第一个元素位置记为begin
    int last = n-1; //将记录序列的最后一个元素位置记为last
    while (begin < last){
        while (A[begin].key < 0){   //从起始位置开始，搜索大于等于0的关键词
            begin++;
        }
        while (A[last].key >= 0){   //从结束位置开始，搜索小于0的关键词
            last--;
        }
        if (begin < last){  //符合条件的话，交换两个元素
            swap(A[begin],A[last]);
        }
    }
}