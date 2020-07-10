#include <iostream>
#include "Standard.h"

void InsertSort_Version_1(List &A){
    int len = sizeof(A)/sizeof(records);
    int i,j;
    A[0].key = -maxsize;
    for (i=1; i<=len; i++){
        j = i;
        while (A[j].key < A[j-1].key){
            swap(A[j],A[j-1]);
            j--;
        }
    }
}

void InsertSort_Version_2(List &A){
    int len = sizeof(A)/sizeof(records);
    int i,j;
    A[0].key = -maxsize;
    for (i=1; i<=len; i++){
        j = i;
        records temp = A[j];
        while (temp.key < A[j-1].key){
            A[j] = A[j-1];
            j--;
        }
        A[j] = temp;
    }
}