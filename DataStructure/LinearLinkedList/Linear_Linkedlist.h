#include <stdio.h>
#include <stdlib.h>
#include "Standard.h"

typedef char ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}*LinkList;

Status GetElem_L(LinkList L,int pos,ElemType &e){
    LinkList p = L->next;
    int i = 1;
    while (p && i<pos){
        p = p->next;
        ++i;
    }
    if (!p || i>pos){
        return ERROR;
    }
    e = p->data;
    return OK;
}

Status ListInsert_L(LinkList &L,int pos,ElemType e){
    LinkList temp = L;
    int i = 0;
    while (temp && i<pos-1){
        temp = temp->next;
        ++i;
    }
    if (!temp || i>pos-1){
        return ERROR;
    }
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = temp->next;
    temp->next = s;
    return OK;
}

Status ListDelete_L(LinkList &L,int pos,ElemType &e){
    LinkList temp = L;
    int i = 0;
    while (temp->next && i<pos-1){
        temp = temp->next;
        ++i;
    }
    if (!(temp->next) || i>pos-1){
        return ERROR;
    }
    LinkList q = temp->next;
    e = q->data;
    temp->next = q->next;
    free(q);
    return OK;
}

void CreateList_L(LinkList &L,int length){
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    for (int i = length;i > 0;--i){
        LinkList temp = (LinkList)malloc(sizeof(LNode));
        scanf(&temp->data);
        temp->next = L->next;
        L->next = temp;
    }
}

void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc){
    LinkList pa = La->next;
    LinkList pb = Lb->next;
    LinkList pc = Lc = La;
    while (pa && pb){
        if (pa->data <= pb->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa?pa:pb;
    free(Lb);
}