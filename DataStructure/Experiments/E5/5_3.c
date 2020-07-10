#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Period{
    int start;
    int end;
}Period;

typedef struct Node{
    Period period;
    int weigh;
    struct Node* next;
}Node,*NodeList; 

NodeList InitNode(){
    NodeList node = (NodeList)malloc(sizeof(Node));
    node->period.start = node->period.end = 0;
    node->weigh = 0;
    node->next = NULL;
    return node;
}

void InsertNode(NodeList node, Period data){
    NodeList temp = node;
    while (data.start<=data.end){
        //首先，通过比较start（开始时间点）找到插入结点的位置。
        //temp指针指向start小于待插入结点（data）的start的最后一个结点。
        while (temp->next!=NULL && temp->next->period.start<data.start){
            temp = temp->next;
        }
        //1. 此时temp是最后一个结点。
        if (temp->next == NULL){    
            //1.1 两个时间段相互独立。处理方法：直接在链表尾插入。
            //如： [1,2] +[3,4] => [1,2]->[3,4]
            if (data.start > temp->period.end){ 
                NodeList newNode = InitNode();
                newNode->period = data;
                newNode->weigh++;
                temp->next = newNode;
                break;
            }
            //1.2 两个时间段在结点处相等。 处理方法：重叠处断开，形成新的结点；改变data的开始时间点，再次进入循环
            //如： [1,2] +[2,3] => [1,1]->[2,2] +[3,3]  ([3,3]段需要重新循环，看作新的data)
            else if (data.start == temp->period.end){   
                NodeList newNode = InitNode();
                newNode->period.start = newNode->period.end = data.start;
                newNode->weigh = temp->weigh+1;
                temp->period.end--;
                temp->next = newNode;
                data.start++;   //此处是因为原来的start形成了新的结点，故+1.
            }
            //1.3 两个时间段互相重叠。有三种可能。
            else {
                //1.3.1 两个时间段各有一段互相重叠。 处理方法：重叠处断开，形成新的结点；改变data的开始时间点，再次进入循环
                //如：[1,3] +[2,4] => [1,1]->[2,3] +[4,4]   ([4,4]段需要重新循环，看作新的data)
                if (temp->period.end < data.end){
                    NodeList newNode = InitNode();
                    newNode->period.start = data.start;
                    newNode->period.end = temp->period.end;
                    newNode->weigh = temp->weigh+1;
                    temp->period.end = data.start-1;
                    temp->next = newNode;
                    data.start = newNode->period.end+1;
                }
                //1.3.2 两个时间段为包含关系，且有一端重叠。 处理方法：重叠处断开，形成新的结点。
                //如： [1,3] +[2,3] => [1,1]->[2,3]
                else if (temp->period.end == data.end){
                    NodeList newNode = InitNode();
                    newNode->period = data;
                    newNode->weigh = temp->weigh+1;
                    temp->period.end = data.start-1;
                    temp->next = newNode;
                    break;
                }
                //1.3.3 两个时间段为包含关系，且两端均不重叠。 处理方法：重叠处断开，两边各形成新的结点。
                //如： [1,3] +[2,2] => [1,1]->[2,2]->[3,3]
                else {  
                    NodeList newNode1 = InitNode();
                    NodeList newNode2 = InitNode();

                    newNode1->period = data;
                    newNode2->period.start = data.end+1;
                    newNode2->period.end = temp->period.end;
                    temp->period.end = data.start-1;
                    
                    newNode1->weigh = temp->weigh+1;
                    newNode2->weigh = temp->weigh;
                    temp->next = newNode1;
                    newNode1->next = newNode2;
                    break;
                }
            }
        }
        //2. 此时temp不是最后一个结点，同时temp后一个结点的start与data的start相等。
        else if (temp->next->period.start == data.start){
            temp = temp->next;  //先进入下一个结点
            //2.1，2.2： 若目标时间段∈data的时间段。  处理方法：目标时间段权值+1， 修改data的start，视为新的data再次进入循环
            //如： [2,3] +[2,3] || [2,3]+[2,4]
            if (temp->period.end <= data.end){  
                temp->weigh++;
                data.start = temp->period.end+1;
            }
            //2.3 若data的时间段在目标时间段内。  处理方法：重叠处断开，形成新的结点。
            //如： [2,4] +[2,3] => [2,3]->[4,4]
            else{
                NodeList newNode = InitNode();
                newNode->period.start = data.start+1;
                newNode->period.end = temp->period.end;
                newNode->weigh = temp->weigh;
                newNode->next = temp->next;

                temp->period = data;
                temp->weigh++;
                temp->next = newNode;
                break;
            }
        }
        //3. 此时temp不是最后一个结点，同时data需要插入在temp结点处（data的start小于temp后一个结点的start）
        else {
            //3.1 若同时涉及多个结点。 处理方法：从最左第一个涉及的结点开始操作，操作完成后修改data的start值，视为新的data再次循环
            //如： [1,3]->[4,4] +[2,4] => [1,1]->[2,3]->[4,4] +[4,4] (后一个[4,4]未与原[4,4]合并，而是在[1,3]操作完成后重新循环，视为新data)
            if (temp->period.end < data.end){
                NodeList newNode = InitNode();
                newNode->period.start = data.start;
                newNode->period.end = temp->period.end;
                newNode->weigh = temp->weigh+1;
                temp->period.end = data.start-1;
                newNode->next = temp->next;
                temp->next = newNode;
                data.start = newNode->period.end+1;
            }
            //3.2，3.3 若只涉及当前temp结点。 处理方法：重叠处断开，形成新的结点，修改data的start值，视为新的data再次循环。
            //如： [1,3]->[4,4] +[2,3] => [1,1]->[2,3]->[4,4] +[4,3](注：此时新的data[4,3]是错误的，故会在判定入口条件时出循环。)
            else { 
                NodeList newNode = InitNode();
                newNode->period = data;
                newNode->weigh = temp->weigh+1;
                newNode->next = temp->next;
                temp->period.end = data.start-1;
                temp->next = newNode;
                data.start = newNode->period.end+1;
            }
        }
    }
}

void DeleteNode(NodeList open, NodeList closed, Period data){
    //open为当前储存时间段信息的链表
    //closed为当前储存重合度最高（权值最大）时间段信息的链表
    NodeList o_temp = open->next;
    NodeList c_temp = closed->next;
    while (o_temp!=NULL && o_temp->period.end < data.start){    //寻找是否有结点需要删除
        //考虑是否要在closed链表中作出修改。比较待删除结点和closed结点的权值大小。
        //1. 若closed中本身没有数据，或者待删除结点和目前已有的最大权值相等，则应将该结点插入到closed中。
        if (c_temp==NULL || o_temp->weigh == c_temp->weigh){
            open->next = o_temp->next;
            o_temp->next = closed->next;
            closed->next = o_temp;
            c_temp = o_temp;
            o_temp = open->next;
        }
        //2. 若待删除结点的权值较大，那么closed中的数据应全部清除，再将该结点插入到closed中。
        else if (o_temp->weigh > c_temp->weigh){
            while (closed->next != NULL){
                closed->next = c_temp->next;
                free(c_temp);
                c_temp = closed->next;
            }
            open->next = o_temp->next;
            o_temp->next = closed->next;
            closed->next = o_temp;
            c_temp = o_temp;
            o_temp = open->next;
        }
        //3. 否则，直接释放该节点。
        else{
            o_temp = o_temp->next;
            free(open->next);
            open->next = o_temp;
        }
    }
}

void swap(int i, int j, Period A[]){
    Period temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void PushDown(int first, int last, Period A[]){
    int r = first;
    while (r<=last/2){
        if (r==last/2 && last%2 == 0){
            if(A[r].start < A[2*r].start){
                swap(r,r*2,A);
            }
            r = last;
        }
        //若左孩子大于等于右孩子，且左孩子大于根节点，交换。
        else if(A[r].start<A[2*r].start && A[2*r].start>=A[2*r+1].start){
            swap(r,r*2,A);
            r*=2;
        }
        //若右孩子比左孩子大，且右孩子大于根节点，交换
        else if(A[r].start<A[2*r+1].start && A[2*r+1].start>A[2*r].start){
            swap(r,r*2+1,A);
            r = 2*r+1;
        }
        else{
            r = last;
        }
    }
}

//采用堆排序，构造start升序序列
void HeapSort(int n, Period A[]){
    int i;
    for (i = n/2; i>=1; i--){   //整理堆
        PushDown(i,n,A);
    }
    for (i=n; i>=2; i--){   //排序
        swap(1,i,A);
        PushDown(1,i-1,A);
    }
}

//由于closed链表的数据为由大到小排列，(为保证美观)构造此函数。
void output(NodeList closed){
    if (closed != NULL){
        output(closed->next);
        printf("%d %d, ",closed->period.start,closed->period.end);
    }
}

void findPeriod(int M, Period A[]){
    NodeList closed = InitNode();
    NodeList open = InitNode();
    Period Max; //设置结束结点。
    Max.start = Max.end = INT_MAX;

    for (int i=1; i<=M; i++){   //对已完成排序的数组A遍历，依次插入链表。
        InsertNode(open,A[i]);
        DeleteNode(open,closed,A[i]);   //每插入一个数据，测试是否有结点需要删除。
    }
    DeleteNode(open,closed,Max);    //所有结点插入完成。通过结束结点Max，比较并删除open链表中的所有结点。

    output(closed->next);
    // NodeList temp = closed->next;
    // while (temp!=NULL){
    //     printf("%d %d, ",temp->period.start,temp->period.end);
    //     temp = temp->next;
    // }
    printf("\b\b \n");

    // for (int i = 1; i <= M; i++){
    //     InsertNode(open,A[i]);
    // }
    // NodeList temp = open->next;
    // while (temp!=NULL){
    //     printf("%d %d %d, ",temp->period.start,temp->period.end,temp->weigh);
    //     temp = temp->next;
    // }
    // printf("\b\b \n");
}

int main()
{
    int N, M; //分别存储时间的段数和学生的个数
    int caseNum = 0;
    Period StuData[1002];

    freopen("5_3_input.in", "r", stdin);
    while(scanf("%d %d",&N,&M)!=EOF){
        caseNum++;
        printf("==== Case %d ====\n",caseNum);
        for(int i = 1; i <= M;i++){
            scanf("%d %d",&(StuData[i].start),&(StuData[i].end));
        }
        HeapSort(M,StuData);
    //    for (int i = 1; i <= M; i++){
    //        printf("%d %d, ",StuData[i].start,StuData[i].end);
    //    }
    //    printf("\b\b \n");
        findPeriod(M,StuData);
    }
    fclose(stdin);

   /* 终端输入
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   */
}

