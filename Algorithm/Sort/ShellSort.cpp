#include <iostream>
#include "Standard.h"

void ShellSort(List &A){
    int len = sizeof(A)/sizeof(records);
    int i,j;
    for (int k=len/2; k>=1; k/=2){
        for (i=k+1; i<=len; i++){
            records temp = A[i];
            j = i-k;
            while (j>0 && temp.key>A[j].key){
                A[j+k] = A[j];
                j -= k;
            }
            A[j+k] = temp;
        }
    }
}