#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
//图的定义使用链式前向星方式构建图
//当然你也可以用自己的方法构建图,如临接矩阵或者临接表
#define INF 2147483647
int ans[maxn];
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
    graph->edges[++graph->tot].start = start;
    graph->edges[graph->tot].end = end;
    graph->edges[graph->tot].weight = weight;

    //链式前向星存储，每加一条边的时候，同一起点的边用next来做链式存储
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

void visit_graph(int n, struct Graph *graph)
{

   
    //debug 函数，提供这种存储方式的遍历过程，方便同学们debug
    for (int i = 1; i <= n; i++) //n个起点
    {
        printf("start with %d\n", i);
        for (int j = graph->head[i]; j != -1; j = graph->edges[j].next) //遍历以i为起点的边
        {
            printf("edges i is start:%d,end:%d,weight is:%d\n", graph->edges[j].start, graph->edges[j].end, graph->edges[j].weight);
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

void forward_propagation(int n_total, int n_input, int n_output, int *input_array, Graph *graph)
{
    for (int i=1; i<=n_total; i++){
        ans[i] = 0; //考虑到ans为全局数组，每次使用时先进行数据更新
    }
    for (int i=1; i<=n_input; i++){
        ans[i] = input_array[i];    //把输入元素赋值到ans数组相应位置
    }
    for (int i=1; i<=n_total-n_output; i++){
        int index = graph->head[i]; //初始化index，从头开始遍历（确保数据为层层读入）
        while (index != -1)
        {
            //为提高代码可读性，首先对相应变量进行处理。
            int start = graph->edges[index].start;
            int end = graph->edges[index].end;
            int weight = graph->edges[index].weight;
            //对终点结点值的更新。（即实现终点结点=起始结点*对应权值的和）
            ans[end] += ans[start]*weight;
            //index值的更新。
            index = graph->edges[index].next;
        }
    }
}

int main()
{
    int input[maxn];
    int n_total, m_total, n_input, n_output;

    //文件输入的方式
    freopen("4_2_input.in", "r", stdin);
    while (scanf("%d%d%d%d", &n_total, &m_total, &n_input, &n_output) != EOF)
    {
        Graph *g = init_graph();
        int start, end, weight;

        for (int i = 1; i <= m_total; i++)
        {
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        for (int i = 1; i <= n_input; i++)
        {
            scanf("%d", &input[i]);
        }
        //结果保存在全局变量ans数组中
        forward_propagation(n_total, n_input, n_output, input, g);

        for (int i = n_total - n_output + 1; i <= n_total; i++)
        {
            printf(i < n_total ? "%d " : "%d\n", ans[i]);
        }
    }
    fclose(stdin);

    /*
    //终端输入的方式进行io
    while (scanf("%d%d%d%d", &n_total, &m_total, &n_input, &n_output) != EOF)
    {

        struct Graph *g = init_graph();
        int x, y, z;
        int start, end, weight;

        for (int i = 1; i <= m_total; i++)
        {
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        for (int i = 1; i <= n_input; i++)
        {
            scanf("%d", &input[i]);
        }
        //结果保存在全局变量ans数组中
        forward_propagation(n_total, n_input, n_output, input, g);

        for (int i = n_total - n_output + 1; i <= n_total; i++)
        {
            printf(i < n_total ? "%d " : "%d\n", ans[i]);
        }
    }
    */
/*
输入输出样例
输入：
8 10 2 1
1 3 2
1 4 1
2 4 3
2 5 3
3 6 4
4 6 2
4 7 2
5 7 7
6 8 2
7 8 1
5 10
输出：
500
*/
    return 0;
}
