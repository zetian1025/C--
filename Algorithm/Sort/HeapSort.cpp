#include <iostream>
#include "Standard.h"

void PushDown(int first, int last, List &A){
    int r = first;
    while (r<=last/2){
        if (r==last/2 && last%2 == 0){
            if(A[r].key > A[2*r].key){
                swap(A[r],A[2*r]);
            }
            r = last;
        }
        else if(A[r].key>A[2*r].key && A[2*r].key<=A[2*r+1].key){
            swap(A[r],A[2*r]);
            r*=2;
        }
        else if(A[r].key>A[2*r+1].key && A[2*r+1].key<A[2*r].key){
            swap(A[r],A[2*r+1]);
            r = 2*r+1;
        }
        else{
            r = last;
        }
    }
}

void HeapSort(int n, List &A){
    int i;
    for (i = n/2; i>=1; i--){
        PushDown(i,n,A);
    }
    for (i=n; i>=2; i--){
        swap(A[1],A[i]);
        PushDown(1,i-1,A);
    }
}