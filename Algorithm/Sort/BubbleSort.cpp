#include <iostream>
#include "Standard.h"

void BubbleSort(List &A){
    int len = sizeof(A)/sizeof(records);
    for (int i=1; i<len; i++){
        for (int j=len; j>i; j--){
            if (A[j].key > A[j-1].key){
                swap(A[j],A[j-1]);
            }
        }
    }
    return;
}

void DoubleBubbleSort(List &A){
    int i = 1;
    int len = sizeof(A)/sizeof(records);
    bool flag = true;
    while (flag){
        flag = false;
        for (int j=len-i+1; j>i; j--){
            if (A[j].key > A[j-1].key){
                flag = true;
                swap(A[j],A[j-1]);
            }
        }
        for (int j=i+1; j<=len-i+1; j++){
            if (A[j].key < A[j+1].key){
                flag = true;
                swap(A[j],A[j+1]);
            }
        }
        i++;
    }
}