#include <iostream>
#include "Standard.h"

void SelectSort(List &A){
    int len = sizeof(A)/sizeof(records);
    int i,j,LowIndex;
    for (i=1; i<=len; i++){
        LowIndex = i;
        for (j=i+1; j<=len; j++){
            if (A[j].key < A[LowIndex].key){
                LowIndex = j;
            }
        }
        swap(A[i],A[LowIndex]);
    }
}