#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode{
    /** 栈中存储的节点 */
  int id;
  struct StackNode *Next;
    /** 可自由添加需要用的变量 */
}StackNode;

typedef struct LinkStack{
    /** 栈 */
  StackNode* top;
  StackNode* base;
  int size;
    /** 可自由添加需要的变量 */
}LinkStack;

LinkStack* InitStack(){
    /** 初始化栈 */
  LinkStack* linkStack = (LinkStack *)malloc(sizeof(LinkStack));
  
  StackNode* InitNode = (StackNode*)malloc(sizeof(StackNode));  //初始化头节点（栈底）
  InitNode->id = 0;
  InitNode->Next = NULL;

  linkStack->base = InitNode;
  linkStack->top = linkStack->base; //初始状态，栈底指针和栈顶指针指向同一节点。
  linkStack->size = 0;
  return linkStack;
}

int StackEmpty(LinkStack *linkStack){
    /** 判断栈是否为空 */
  return (linkStack->size == 0);
}

void Push(LinkStack *linkStack,int ele){
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->id = ele;
    node->Next = NULL;
    linkStack->top->Next = node;    //栈中存入下一个元素，放在链表尾。
    linkStack->top = node;  //更新栈顶指针。
    linkStack->size++;
}

void Pop(LinkStack* linkStack){
    /** 将一个节点弹出栈 */
    if (StackEmpty(linkStack)){   //空栈情况，单独考虑
        return;
    }
    StackNode* p = linkStack->base;
    while (p->Next != linkStack->top){  //遍历链表，直至下一项为栈顶
        p = p->Next;
    }
    //释放栈顶元素，栈顶指针重新赋值
    free(linkStack->top);
    linkStack->top = p;
    p->Next = NULL;
    linkStack->size--;
}

int GetTop(LinkStack* linkStack){
    /** 若栈不空，返回栈的栈顶元素 */
    if (StackEmpty(linkStack)){
        return 0;
    }
    return linkStack->top->id;
}

int StackLength(LinkStack* linkStack){
    /** 返回栈的长度 */
    return linkStack->size;
}



int SeqLegal(int in[],int out[],int num){
    /** 实验内容1:判断输入的出站序列是否可由输入的进站序列通过进出栈得到
     可行返回1，不可行返回0
     */
    //初始化三个栈。
    LinkStack* inStack = InitStack();   //用于存放待出站的火车。
    LinkStack* outStack = InitStack();  //用于存放目标入栈的序列。
    LinkStack* tempStack = InitStack(); //用于模拟中转火车站。

    int i;
    for (i=0;i<num;i++){    //将入站、出站次序压入对应栈中
        Push(inStack,in[num-i-1]);
        Push(outStack,out[num-i-1]);
    }
    while (!StackEmpty(outStack))
    {
        if (GetTop(outStack) == GetTop(inStack)){   //1.若栈顶元素相同，一起出栈。
            Pop(outStack);
            Pop(inStack);
        }else if(GetTop(outStack) == GetTop(tempStack)){    //2.若栈顶元素相同，一起出栈。
            Pop(outStack);
            Pop(tempStack);
        }else if(!StackEmpty(inStack)){ //3.若此时栈顶元素不同，且待出栈序列不为空，则转移一个元素至temp栈。
            Push(tempStack,GetTop(inStack));
            Pop(inStack);
        }else{  //4.若栈顶元素均不同，且待出栈序列为空，说明此时已经无法进行操作。（temp->out）
            return 0;
        }
    }
    return 1;
}

typedef struct QueueNode{
    /** 队列节点 */
    int id;
    struct QueueNode* next;
}QueueNode;

typedef struct Queue{
    /** 队列 */
    QueueNode *front;
    QueueNode *rear;
    int size;
}LinkQueue;

LinkQueue* InitQueue(){
    /** 初始化队列 */
    LinkQueue* linkQueue = (LinkQueue*) malloc(sizeof(LinkQueue));
    linkQueue->front = linkQueue->rear = (QueueNode *)malloc(sizeof(QueueNode));
    linkQueue->front->next = NULL;
    linkQueue -> size = 0;
    return linkQueue;
}

int QueueEmpty(LinkQueue* linkQueue){
    /** 判断队列是否为空 */
    return(linkQueue->size == 0);
}

void EnQueue(LinkQueue *linkQueue,int ele){
    /** 入队 */
    //对入队元素的初始化：
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->next = linkQueue->front->next;    //指向原队首元素
    node->id = ele;

    linkQueue->front->next = node;  //入队元素更新为新的队首元素
    if (QueueEmpty(linkQueue)){ //为首个入队的元素：更新队尾指针
        linkQueue->rear = node;
    }
    linkQueue->size++;
}

void DeQueue(LinkQueue *linkQueue){
    /** 出队 */
    if (QueueEmpty(linkQueue)){ //若队列为空，单独考虑
        return;
    }
    QueueNode* p = linkQueue->front;
    while (p->next != linkQueue->rear){ //遍历队列，直至下个元素为队尾元素
        p = p->next;
    }
    free(linkQueue->rear);
    linkQueue->rear = p;
    p->next = NULL;
    linkQueue->size--;
}

int QueueLength(LinkQueue *linkQueue){
    /** 队列长度 */
    return (linkQueue->size);
}

int GetHead(LinkQueue *linkQueue){
    /** 返回队头 */
    return (linkQueue->front->next->id);
}

int GetRear(LinkQueue *linkQueue){
    /** 返回队尾 */
    return (linkQueue->rear->id);
}

int findClosestQueue(LinkQueue *railQueue[],int usedQueue,int curTrain){
    /**  找到最合适的火车轨道 */
    int closestIdx = -1;    //若找不到：返回-1
    
    /** 寻找最合适的火车轨道  */
    //遍历此时的所有已使用火车轨道。
    //条件1：此时火车轨道没有火车（即队列为空）。
    //条件2：此时的队首元素小于待入队的元素。(最小元素先出队列)
    int pos;
    for (pos=0;pos<usedQueue;pos++){
        if (QueueEmpty(railQueue[pos]) || GetHead(railQueue[pos])<curTrain){
            return pos;
        }
    }

    return closestIdx;
}

int minBufferQueue(int out[],int num){
    /** 实验内容2:求解所需缓冲轨道的最小值*/
    LinkQueue *railQueue[num]; //指针数组，记录各缓存轨道的火车，有与火车数相等的轨道数时一定可行
    for(int i = 0;i < num;i++){
        railQueue[i] = InitQueue();
    }
    int usedQueue = 0;      //已使用的队列数
    int arrangedTrain = 0;  //已安排的火车
    int curTrain = 0;   //当前正在尝试安排的火车（0~num-1）
    int MinTrainId = 1; //当前最小的火车编号（即待出队列元素）
    
    /**
     当火车未完全安排完时
     从其中找到最合适放置的轨道
     放置火车
     */
    while (arrangedTrain < num){
        int position = findClosestQueue(railQueue,usedQueue,out[curTrain]); //找到适合的位置
        if (position == -1){
            EnQueue(railQueue[usedQueue++],out[curTrain]);  //情况1：需使用新的轨道
        } else{
            EnQueue(railQueue[position],out[curTrain]); //情况2：可使用已有轨道
        }
        curTrain++; //安排完毕，增1
        
        //在安排完一列火车后，需对已使用轨道遍历，判断是否有火车可以出站（出队列）
        int i;
        for (i=0;i<usedQueue;i++){
            //条件1：轨道上有火车（队列非空） 
            //条件2：火车的编号为所需要的编号（此时的最小编号）
            if (!QueueEmpty(railQueue[i]) && GetRear(railQueue[i])==MinTrainId){
                DeQueue(railQueue[i]);
                MinTrainId++;   //下一个待出站的火车编号。
                arrangedTrain++;    //一列火车安排完成。
                i=0;    //重新开始遍历所有的轨道。
            }
        }
    }
    return usedQueue;
}

int main()
{
    int trainNum;
    int count = 0;
    freopen("TestTrain.in", "r", stdin);
    
    while(scanf("%d",&trainNum)!=EOF){
        count++;
        int trainIn[trainNum];
        int trainOut[trainNum];
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainIn[i]);
        }
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainOut[i]);
        }
        printf("====Case %d====\n",count);
        // 实验内容1
        if(SeqLegal(trainIn,trainOut,trainNum)){
            printf("The output train sequence is Possible\n");
        }else{
            printf("The output train sequence is impossible\n");
        }
        // 实验内容2
        printf("To recover the order, %d buffer queue is needed:\n",minBufferQueue(trainOut, trainNum));

    }
    fclose(stdin);
    system("pause");
    return 0;
}
