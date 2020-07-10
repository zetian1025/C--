#include "Standard.h"
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq(SqList &L){
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if (!L.elem){
        exit(OVERFLOW);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
};

Status ListInsert_Sq(SqList &L,int pos,ElemType e){
    if (pos<1 || pos>L.length+1){
        return ERROR;
    }
    if (L.length >= L.listsize){
       ElemType* newbase = (ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
       if (!newbase){
           exit(OVERFLOW);
       }
       L.elem = newbase;
       L.listsize += LISTINCREMENT;
    }
    ElemType* q = &(L.elem[pos-1]);
    for (ElemType* p = &(L.elem[L.length-1]);p >= q;--p){
        *(p+1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
}

Status ListDelete_Sq(SqList &L,int pos,ElemType & e){
    if ((pos<1) || (pos>L.length)){
        return ERROR;
    }
    ElemType* p = &(L.elem[pos-1]);
    e = *p;
    ElemType* q = L.elem + L.length -1;
    for (++p;p<=q;++p){
        *(p-1) = *p;
    }
    --L.length;
    return OK;
}

int LocateElem_Sq(SqList L,ElemType e,Status(*compare)(ElemType,ElemType)){
    int i = 1;
    ElemType* p = L.elem;
    while (i<=L.length && !(*compare)(*p++,e)){
        ++i;
    }
    if (i<=L.length){
        return i;
    }
    else return 0;
}

void MergeList_Sq(SqList La,SqList Lb,SqList &Lc){
    ElemType* pa = La.elem;
    ElemType* pb = Lb.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;
    ElemType* pc = Lc.elem = (ElemType*)malloc(Lc.listsize*sizeof(ElemType));
    if (!Lc.elem){
        exit(OVERFLOW);
    }
    ElemType* pa_last = La.elem + La.length -1;
    ElemType* pb_last = Lb.elem + Lb.length -1;
    while (pa<=pa_last && pb<=pb_last){
        if (*pa <= *pb){
            *pc++ = *pa++;
        }
        else{
            *pc++ = *pb++;
        }
    }
    while (pa <= pa_last){
        *pc++ = *pa++;
    }
    while (pb <= pb_last){
        *pc++ = *pb++;
    }
}