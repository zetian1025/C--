#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef struct List{
    ElemType data;
    struct List *next;
    struct List *prior;
}*DoubleLinkedList,List;

void BubbleSort(DoubleLinkedList L){
    DoubleLinkedList p = L->next;
    bool flag = false;
    while (!flag){
        p = L->next;
        flag = true;
        while (p->next != NULL){
            if (p->data > p->next->data){
                ElemType temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
                flag = false;
            }
            p = p->next;
        }
    }    
}

int SearchElem(DoubleLinkedList L,ElemType elem){
    DoubleLinkedList p = L->next;
    int pos = 1;
    while (p && p->data!=elem){
        p = p->next;
        pos++;
    }
    if (!p){
        return 0;
    }
    else{
        return pos;
    }
}

bool InsertElem(DoubleLinkedList L,ElemType elem){
    DoubleLinkedList p = L->next;
    DoubleLinkedList bp = p->prior;
    while (p && p->data < elem){
        bp = p;
        p = p->next;
    }
    DoubleLinkedList newElem;
    if (!(newElem = (DoubleLinkedList)malloc(sizeof(List)))){
        return false;
    }
    if (!p){
        bp->next = newElem;
        newElem->prior = bp;
        newElem->next = p;
        newElem->data = elem;
    }
    else{
        newElem->data = elem;
        newElem->next = p;
        p->prior->next = newElem;
        newElem->prior = p->prior;
        p->prior = newElem;
    }
    return true;
}

bool DeleteElem(DoubleLinkedList L,ElemType elem){
    int pos = 0;
    while (((pos = SearchElem(L,elem)) != 0)){
        DoubleLinkedList p = L->next;
        while (pos > 1){
            p = p->next;
            pos--;
        }
        if (p->next == NULL){
            p->prior->next = NULL;
        }
        else{
            p->prior->next = p->next;
            p->next->prior = p->prior;
        }
        free(p);
    }
    if (pos != 0){
        return false;
    }
    return true;
}

int ListLength(DoubleLinkedList L){
    int len = 0;
    DoubleLinkedList p = L->next;
    while (p){
        p = p->next;
        len++;
    }
    return len;
}

void ShowList(DoubleLinkedList L){
    int len = ListLength(L);
    DoubleLinkedList p = L->next;
    while (len-->1){
        printf("%d->",p->data);
        p = p->next;
    }
    printf("%d\n",p->data);
}

void ReverseList(DoubleLinkedList L){
    DoubleLinkedList head = L->next;
    DoubleLinkedList tail = L->next;
    while (tail->next != NULL){
        tail = tail->next;
    }

    ElemType temp;
    while (head != tail && tail->next != head){
        temp = head->data;
        head->data = tail->data;
        tail->data = temp;

        head = head->next;
        tail = tail->prior;
    }
}

ElemType LocateElem(DoubleLinkedList L,int pos){
    DoubleLinkedList p = L->next;
    while (--pos){
        p = p->next;
    }
    return p->data;
}

ElemType LocateMiddleElem(DoubleLinkedList L){
    int len = ListLength(L);
    if (len%2 == 0){
        ElemType elem1 = LocateElem(L,len/2);
        ElemType elem2 = LocateElem(L,len/2+1);
        return (elem1+elem2)/2;
    }
    else{
        return LocateElem(L,(len+1)/2);
    }
}

ElemType LocateElemFromLast(DoubleLinkedList L,int pos){
    DoubleLinkedList p = L->next;
    while (p->next != NULL){
        p = p->next;
    }
    while (--pos>0){
        p = p->prior;
    }
    return p->data;
}

bool MakeList(FILE* fp,DoubleLinkedList L){
    L->prior = NULL;
    L->next = NULL;

    DoubleLinkedList p = L;
    while (!feof(fp)){
        DoubleLinkedList temp = (DoubleLinkedList)malloc(sizeof(List));
        fscanf(fp,"%d",&(temp->data));
        temp->prior = p;
        p->next = temp;
        temp->next = NULL;
        p = p->next;
    }

    BubbleSort(L);
    return true;
}

#endif