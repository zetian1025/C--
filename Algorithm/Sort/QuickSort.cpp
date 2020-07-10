#include <iostream>
#include "Standard.h"

void QuickSort(List &A, int begin, int end){
    int v = FindPivot(A,begin,end);
    if (v){
        KeyType Key = A[v].key;
        int PivotIndex = Partion(A,begin,end,Key);
        QuickSort(A,begin,PivotIndex-1);
        QuickSort(A,PivotIndex,end);
    }
}

int FindPivot(List A, int begin, int end){
    int index = begin;
    KeyType FirstKey = A[index].key;
    for (; index<=end; index++){
        if (A[index].key > FirstKey){
            return index;
        }
        else if (A[index].key < FirstKey){
            return begin;
        }
    }
    return 0; 
}

int Partion(List &A, int start, int end, KeyType key){
    int L = start;
    int R = end;
    do{
        swap(A[L],A[R]);
        while (A[L].key < key){
            L++;
        }
        while (A[R].key >= key){
            R++;
        }
    } while (L <= R);
    return L;
}