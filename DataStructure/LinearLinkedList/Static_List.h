//About Static List:
//A static list has two lists.
//One is to store data(Static list itself,the real one)
//The other is called "Alternate Linked List",which is used to store the haven't-used nodes.
//Common Sense:The first space is the head node of the Alternate list.
//              and the second space is the head node of the Real list.
#include "Standard.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

typedef int ElemType;
typedef struct{
    ElemType data;
    int cur;
}SLinkList[MAXSIZE];

int LocateElem_SL(SLinkList S,ElemType e){
    int i = S[0].cur;
    while (i && S[i].data!=e){
        i = S[i].cur;
    }
    return i;
}

void InitSpace_SL(SLinkList &space){
    for (int i=0;i<MAXSIZE-1;i++){
        space[i].cur = i+1;
    }
    space[MAXSIZE-1].cur = 0;
}

//关于malloc函数：space[0]是备用链表的头“指针”
//若space[0].cur不为0，说明链表未占满，也代表还有空闲节点。
//若想要使用空闲节点，malloc函数会自动选择下一个空闲节点。
//这也表示，只有space[0].cur所指向的节点可以确定为空闲节点。
int Malloc_SL(SLinkList &space){
    int i = space[0].cur;
    if (space[0].cur){
        space[0].cur = space[i].cur;
    }
    return i;
}

//同上malloc函数。
void Free_SL(SLinkList &space,int k){
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

void difference(SLinkList &space,int &S){
    int m,n;
    InitSpace_SL(space);
    S = Malloc_SL(space);
    int r = S;
    scanf("%d%d",&m,&n);
    for (int j=1;j<=m;j++){
        int i = Malloc_SL(space);
        scanf("%d",space[i].data);
        space[r].cur = i;
        r = i;
    }
    space[r].cur = 0;
    for (int j=1;j<=n;j++){
        int b;
        scanf("%d",&b);
        int p = S;
        int k = space[S].cur;
        while (k!=space[r].cur && space[k].data!=b){
            p = k;
            k = space[k].cur;
        }
        if (k == space[r].cur){
            int i = Malloc_SL(space);
            space[i].data = b;
            space[i].cur = space[r].cur;
            space[r].cur = i;
        }
        else{
            space[p].cur = space[k].cur;
            Free_SL(space,k);
            if (r == k){
                r = p;
            }
        }
    }
}