#include "Standard.h"
#include <iostream>

void OESort(List &A, int n) {
    int i, flag;
    do {
        flag = 0;
        for (i = 0; i < n; i += 2)
            if (A[i].key > A[i + 1].key) {
                flag = 1;
                swap(A[i], A[i + 1]);
            }
        for (i = 1; i < n; i += 2)
            if (A[i].key > A[i + 1].key) {
                flag = 1;
                swap(A[i], A[i + 1]);
            }
    } while (flag);
}
