#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct Node{
    int data;
    int bf;
    struct Node *lchild,*rchild;
};
typedef struct Node* AVLT;
int unbalanced;

void LeftRotation(AVLT& T,int& unbalanced){
    AVLT gc,lc;
    lc = T->lchild;
    if (lc->bf == 1){
        T->lchild = lc->rchild;
        lc->rchild = T;
        T->bf = 0;
        T = lc;
    }
    else{
        gc = lc->rchild;
        lc->rchild = gc->lchild;
        gc->lchild = lc;
        T->lchild = gc->rchild;
        gc->rchild = T;
        switch(gc->bf){
            case 1:
                T->bf = -1;
                lc->bf = 0;
                break;
            case 0:
                T->bf = lc->bf = 0;
                break;
            case -1:
                T->bf = 0;
                lc->bf = 1;
        }
        T = gc;
    }
    T->bf = 0;
    unbalanced = false;
    return ;
}
void RightRotation(AVLT& T,int& unbalanced){
    AVLT gc,rc;
    rc = T->rchild;
    if (rc->bf == 1){
        T->rchild = rc->lchild;
        rc->lchild = T;
        T->bf = 0;
        T = rc;
    }
    else{
        gc = rc->lchild;
        rc->lchild = gc->rchild;
        T->rchild = gc->lchild;
        gc->lchild = T;
        gc->rchild = rc;
        switch(gc->bf){
            case 1:
                rc->bf = -1;
                T->bf = 0;
                break;
            case 0:
                T->bf = rc->bf = 0;
                break;
            case -1:
                rc->bf = 0;
                T->bf = -1;
                break;
        }
        T = gc;
    }
    T->bf = 0;
    unbalanced = false;
    return;
}
void AVLInsert(AVLT& T,int R,int& unbalanced){
    if (!T){
        unbalanced = true;
        T = new Node;
        T->data = R;
        T->lchild = T->rchild = nullptr;
        T->bf = 0;
    }
    else if(R < T->data){
        AVLInsert(T->lchild,R,unbalanced);
        if (unbalanced){
            switch (T->bf)
            {
            case -1:
                T->bf = 0;
                unbalanced = false;
                break;
            case 0:
                T->bf = 1;
                break;
            case 1:LeftRotation(T,unbalanced);
            }
        }
    }
    else if (R >= T->data){
        AVLInsert(T->rchild,R,unbalanced);
        if (unbalanced){
            switch (T->bf){
                case 1:
                    T->bf = 0;
                    unbalanced = false;
                    break;
                case 0:
                    T->bf = -1;
                    break;
                case -1:
                    RightRotation(T,unbalanced);
            }
        }
    }
    else{
        unbalanced = false;
    }
}