#include <iostream>
#include "Standard.h"

void Merge(int l, int m, int n, List A, List &B){
    int i,j,k,t;
    i = k = l;
    j = m+1;
    while ((i<=m)&&(j<=n)){
        if (A[i].key <= A[j].key){
            B[k++] = A[i++];
        }
        else{
            B[k++] = A[j++];
        }
    }
    if (i>m){
        for (t=j; t<=n; t++){
            B[k+t-j] = A[t];
        }
    }
    else{
        for (t=i; t<=m; t++){
            B[k+t-i] = A[t];
        }
    }
}

void MPass(int n, int l, List A, List &B){
    int i = 1;
    int t;
    while (i <= (n-2*l+1)){
        Merge(i,i+l-1,i+2*l-1,A,B);
        i = i+2*l;
    }
    if ((i+l-1)>n){
        Merge(i,i+l-1,n,A,B);
    }
    else
    {
        for (t=i; t<=n; t++){
            B[t] = A[t];
        }
    }
}

void T_W_sort(int n, List &A){
    int l = 1;
    List B;
    while (l < n){
        MPass(n,l,A,B);
        l*=2;
        MPass(n,l,B,A);
        l*=2;
    }
}