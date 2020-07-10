#include "Standard.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode,*DuLinkList;

int ListLength(DuLinkList &L){
    int i;
    for (i=0;L!=NULL;i++){
        L = L->next;
    }
    return i;
}

DuLinkList GetElemP_DuL(DuLinkList L,int pos){
    DuLinkList p = L->next;
    int i = 1;
    while (p && i<pos){
        p = p->next;
        ++i;
    }
    if (!p || i>pos){
        return ERROR;
    }
    return p;
}

Status ListInsert_DuL(DuLinkList &L,int pos,ElemType e){
    DuLinkList p;
    if (!(p=GetElemP_DuL(L,pos))){
        return ERROR;
    }
    
    DuLinkList s;
    if (!(s=(DuLinkList)malloc(sizeof(DuLNode)))){
        return ERROR;
    }
    s->data = e;
    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    return OK;
}

Status ListDelete_DuL(DuLinkList &L,int pos,ElemType &e){
    DuLinkList p;
    if (!(p=GetElemP_DuL(L,pos))){
        return ERROR;
    }
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}