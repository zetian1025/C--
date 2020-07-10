#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

typedef int ElementType;

struct BFNode{
    ElementType data;
    int bf;
    BFNode* lchild;
    BFNode* rchild;
};

int BF_Depth(BFNode* T){
    if (T == nullptr){
        return 0;
    }
    else{
        if (T->bf == 1 || T->bf == 0){
            return 1+BF_Depth(T->lchild);
        }
        else{
            return 1+BF_Depth(T->rchild);
        }
        
    }
}