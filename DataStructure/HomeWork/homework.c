//设计算法，将已有用邻接矩阵存储的带权图转换成邻接表表示
#include <stdio.h>
#include <stdlib.h>
#define INFINITY 2000
#define MAX_VERTEX_NUM 20
//邻接矩阵结构定义
typedef struct ArcCell{
    int adj;    //邻接状态
    int weight;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
    char vex[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum,arcnum;
}Mgraph;
//邻接表结构定义
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;    //下一个邻接点  
    int weight;
}ArcNode;
typedef struct Vnode{
    char data;
    ArcNode *firstarc;  //第一个邻接点
}Vnode,AdjList[MAX_VERTEX_NUM];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

void transformation(ALGraph* GL,Mgraph GM){
    //新建邻接表。并使顶点、边的数量与邻接矩阵一致。
    GL = (ALGraph*)malloc(sizeof(ALGraph));
    GL->vexnum = GM.vexnum;
    GL->arcnum = GM.arcnum;

    for (int i=0;i<GL->vexnum;i++){
        //遍历GM矩阵。首先将GL表中的第一个邻接点均赋成NULL，并将表中元素初始化为矩阵中的元素。
        GL->vertices[i].firstarc = NULL;
        GL->vertices[i].data = GM.vex[i];
        for (int j=0;j<GL->vexnum;j++){
            //遍历矩阵的某一行。若某处不为零，说明两顶点之间有边相连。
            //此时，将在邻接表中同步增加该邻接点。
            if (GM.arcs[i][j].adj != 0){
                ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = GM.arcs[i][j].weight;
                p->nextarc = GL->vertices[i].firstarc;
                GL->vertices[i].firstarc = p;
            }
        }
    }
}