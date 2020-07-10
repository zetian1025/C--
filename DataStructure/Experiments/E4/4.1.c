#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
//图的定义使用链式前向星方式构建图
//当然你也可以用自己的方法构建图,如临接矩阵或者临接表
#define INF 2147483630
int ans[maxn];
int path[maxn];
typedef struct Edge
{
    int start, end, weight;
    //该边，同一起点的上一边在edges中存储的下标。以next作为链式寻找同一起点的所有边
    int next;
}Edge;

typedef struct Graph
{
    struct Edge edges[maxm];

    //head[i] 记录的是以i为起点的边集中第一条边在edges中的index,
    int head[maxn];

    //当前第几条边
    int tot;
}Graph;

Graph *init_graph()
{
    Graph *new_graph = (Graph *)malloc(sizeof(Graph));
    new_graph->tot = 0;
    memset(new_graph->head, -1, sizeof(new_graph->head));
    return new_graph;
}

void add_edge(int start, int end, int weight, Graph *graph)
{
    //提供这种存储加边方式
    graph->edges[++graph->tot].start = start;
    graph->edges[graph->tot].end = end;
    graph->edges[graph->tot].weight = weight;

    //链式前向星存储，每加一条边的时候，同一起点的边用next来做链式存储
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

void visit_graph(int n, Graph *graph)
{
    //debug 函数，提供这种存储方式的遍历过程，方便同学们debug
    for (int i = 1; i <= n; i++) //n个起点
    {
        printf("start with %d\n", i);
        for (int j = graph->head[i]; j != -1; j = graph->edges[j].next) //遍历以i为起点的边
        {
            printf("Edge i is start:%d,end:%d,weight is:%d\n", graph->edges[j].start, graph->edges[j].end, graph->edges[j].weight);
        }
    }
    
    //遍历图中同一起点所有边的方法
    
    // int  index;
    // index = graph->head[startpoint];
    // while (index!=-1)
    // {
    //     /* code */
    //     //do something
        
    //     index = graph->edges[index].next;
    // }
    
    
}

void visit(int endpoint, int startpoint){
    if (endpoint != startpoint){
        visit(path[endpoint],startpoint);
        printf("->%d",endpoint);
    }
    else{
        printf("In path: %d",startpoint);
    }
}

int get_min_time(int n, int startpoint, Graph *graph)
{
    int index = graph->head[startpoint];
    int MinPoint = startpoint;  //当前最短时间结点编号
    int MinPath = 0;    //最短要求时间
    int count = n;
    int FLAG[n+1];  //访问标记

    for (int i=1; i<=n; i++){
        FLAG[i] = 0;    //将访问标记初始化为0（均未访问过）
        ans[i] = INF;   //将结点间的距离设为INF（无限长）
        path[i] = startpoint;
    }

    //对于起始结点，给ans数组赋初值。
    while (index != -1){
        ans[graph->edges[index].end] = graph->edges[index].weight;
        if (ans[graph->edges[index].end] < ans[MinPoint]){
            MinPoint = graph->edges[index].end; //并求出此时距离初始结点最近的结点。
        }
        index = graph->edges[index].next;
    }
    ans[startpoint] = 0;    //将到本结点的时间设为0。
    FLAG[startpoint] = 1;   //标记为已访问过。

    while (--count>0){
        index = graph->head[MinPoint];   //当前结点（index）赋值。
        FLAG[MinPoint] = 1;    //标记为已访问过（无需再次比较）
        while (index != -1 && index != 0){  //两种情况：①到达尾结点 ②本身无子结点
            int end = graph->edges[index].end;  //指向结点设为end
            int start = graph->edges[index].start;  //起始结点设为start
            if (FLAG[end] != 1){    //若为未访问过的结点
                if (ans[start]+graph->edges[index].weight < ans[end]){
                    ans[end] = ans[start]+graph->edges[index].weight;
                    path[end] = start;  //对路径的更新
                }
                MinPoint = ans[end]<ans[MinPoint]?end:MinPoint; //求出此时距离start最近的结点。
            }
            index = graph->edges[index].next;
        }
    }

    for (int i=1; i<=n; i++){
        if (ans[i] == INF){
            return -1;
        }
        if (ans[i]>MinPath){
            MinPath = ans[i];
            MinPoint = i;
        }
    }
    visit(MinPoint,startpoint);
    printf("\n");
    return MinPath;
}
int main()
{
    int n, m, startpoint, min_time;

    //文件读入的方式
    freopen("4_1_input.in", "r", stdin);
    while (scanf("%d%d%d", &n, &m, &startpoint) != EOF)
    {
        //scanf("%d%d%d", &n, &m, &startpoint);
        Graph *g = init_graph();
        int start, end, weight;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        if (g->tot == 0){
            printf("Min_time: %d\n\n",-1);
        }
        else{
            min_time = get_min_time(n, startpoint, g);
            printf("Min_time: %d\n\n", min_time);
        }
    }
    fclose(stdin);

    //终端输入的方式
    /*
    while(scanf("%d%d%d", &n, &m, &startpoint)!=EOF){
    //scanf("%d%d%d", &n, &m, &startpoint);
    struct Graph* g =init_graph();
    int start, end, weight;
    for (int i=1; i<=m; i++){
        scanf("%d%d%d", &start, &end, &weight);
        add_edge(start, end, weight,g);
    }

    min_time=get_min_time(n,startpoint,g);
    printf("%d\n",min_time);
    }
    */
    return 0;
    /*
    测试输入输出形式：
输入：
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4

输出：
4
    */
}
