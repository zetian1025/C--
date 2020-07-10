#include "Standard.h"

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}*Link,*Position;

typedef struct{
    Link Head,tail;
    int len;
}LinkList;

Status MakeNode(Link &p,ElemType e);
    //分配由p指向的值为e的节点，并返回OK；若分配失败，则返回ERROR
void FreeNode(Link &p);
    //释放p所指节点
Status InitList(LinkList &L);
    //构造一个空的线性链表L
Status DestroyLIst(LinkList &L);
    //销毁线性链表L，L不再存在
Status ClearList(LinkList &L);
    //将线性链表L重置为空表，并释放原链表的节点空间
Status InsFirst(Link h,Link s);
    //已知h指向线性链表的头节点，将s所指向节点插入在第一个节点前
Status DelFirst(Link h,Link &q);
    //已知h指向线性链表的头节点，删除链表中的第一个节点并以q返回
Status Append(LinkList &L,Link s);
    //将指针s所指（彼此以指针相链）的遗传节点链接在线性链表L的最后一个节点
    //并改变链表L的尾指针指向新的尾节点
Status Remove(LinkList &L,Link &q);
    //删除线性链表L中的尾节点并以q返回，改变链表L的尾指针指向新的尾节点
Status InsBefore(LinkList &L,Link &p,Link s);
    //已知p指向线性链表L中的一个节点，将s所指向节点插入在p所指向节点之后
    //并修改指针p指向新插入的节点
Status InsAfter(LinkList &L,Link &p,Link s);
    //已知p指向线性链表L中的一个节点，将s所指节点插入在p所指节点之后
    //并修改指针p指向新插入的节点
Status SetCurElem(Link &p,ElemType e);
    //已知p指向线性链表中的一个节点，用e更新p所指节点中数据元素的值
ElemType GetCurElem(Link p);
    //已知p指向线性链表中的一个节点，返回p所指节点中数据元素的值
Status ListEmpty(LinkList L);
    //若线性链表L为空表，则返回TRUE,否则返回FALSE
int ListLength(LinkList L);
    //返回线性链表L中元素个数
Position GetHead(LinkList L);
    //返回线性链表L中头节点的位置
Position GetLast(LinkList L);
    //返回线性链表L中最后一个节点的位置
Position PriorPos(LinkList L,Link p);
    //已知p指向线性链表L中的一个节点，返回p所指节点的直接前驱的位置
    //若无前驱，则返回NULL
Position NextPos(LinkList L,Link p);
    //已知p指向线性链表L中的一个节点，返回p所指节点的直接后继的位置
    //若无后继，则返回NULL
Status LocatePos(LinkList L,int i,Link&p);
    //返回p指示线性链表L中的第i个节点的位置并返回OK，i非法时返回ERROR    
Position LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType));
    //返回线性链表L中第一个与e满足函数compare()判定关系的元素的位置
    //若不存在这样的元素，则返回NULL
Status ListTraverse(LinkList L,Status(*visit)());
    //依次对L的每个元素调用函数visit()。一旦visit()失败，则操作失败；



Status ListInsert_L(LinkList &L,int i,ElemType e){
    //在带头节点的单链线性表L的第i个元素之前插入元素e
    Link pos1;
    Link pos2;
    if (!LocatePos(L,i-1,pos1)){
        return ERROR;
    }
    if (!MakeNode(pos2,e)){
        return ERROR;
    }
    InsFirst(pos1,pos2);
    return OK;
}

Status MergeLIst_L(LinkList &La,LinkList &Lb,LinkList &Lc,int(*compare)(ElemType,ElemType)){
    Link pos;
    if (!InitList(Lc)){
        return ERROR;
    }
    Position ha = GetHead(La);
    Position hb = GetHead(Lb);
    Position pa = NextPos(La,ha);
    Position pb = NextPos(Lb,hb);
    while (pa && pb){
        ElemType a = GetCurElem(pa);
        ElemType b = GetCurElem(pb);
        if ((*compare)(a,b) <= 0){
            DelFirst(ha,pos);
            Append(Lc,pos);
            pa = NextPos(La,ha);
        }
        else{
            DelFirst(hb,pos);
            Append(Lc,pos);
            pb = NextPos(Lb,hb);
        }
    }
    if (pa){
        Append(Lc,pa);
    }
    else {
        Append(Lc,pb);
    }
    FreeNode(ha);
    FreeNode(hb);
    return OK;
}