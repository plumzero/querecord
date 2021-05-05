
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;

/**
 * 邻接表表示
 */

#define MAXSIZE 100         /** 最大顶点个数 */
typedef enum {
    DG,     // 有向图
    DN,     // 有向网
    UG,     // 无向图
    UN      // 无向网
} GraphKind;

/** 弧(边) */
typedef struct ArcNode {
    int adjvex;                 /** 弧指向的顶点的位置 */
    InfoPtr * info;             /** 与弧相关的信息 */
    struct ArcNode * nextarc;   /** 指示下一个与该顶点相邻接的顶点 */
} ArcNode;

/** 顶点 */
typedef struct VNode {
    VertexType data;            /** 存储顶点 */
    ArcNode * firstarc;         /** 指示第一个与该顶点邻接的顶点(该顶点的一条边或弧) */
} VNode, AdjList[MAXSIZE];

typedef struct {
    AdjList vertex;             /** 顶点列表 */
    int vexnum, arcnum;         /** 图的顶点数目与弧的数目 */
    GraphKind kind;             /** 图的类型 */
} AdjGraph;

/** 返回图中顶点对应的位置 */
int LocateVertex(AdjGraph G, VertexType v)
{
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (strcmp(G.vertex[i].data, v) == 0)
            return i;
    }

    return -1;
}
/** 采用邻接表存储结构，创建无向图 */
void CreateGraph(AdjGraph * G)
{
    int i, j, k;
    VertexType v1, v2;      /** 定义两个顶点 v1 和 v2 */
    ArcNode * p;
    printf("请输入图的顶点数，边数(逗号分隔): ");
    scanf("%d,%d", &(*G).vexnum, &(*G).arcnum);
    
    printf("请输入%d个顶点的值:\n", G->vexnum);
    for (i = 0; i < G->vexnum; i++) {
        scanf("%s", G->vertex[i].data);
        G->vertex[i].firstarc = NULL;       /** 将相关联的顶点置为空 */
    }
    
    printf("请输入弧尾和弧头(以空格作为间隔):\n");
    for (k = 0; k < G->arcnum; k++) {       /** 建立边链表 */
        scanf("%s%s", v1, v2);
        i = LocateVertex(*G, v1);
        j = LocateVertex(*G, v2);
        /** j为入边，i为出边，创建邻接表 */
        p = (ArcNode*)malloc(sizeof(ArcNode));
        assert(p);
        p->adjvex = j;
        p->info = NULL;
        p->nextarc = G->vertex[i].firstarc;     /** 头插法 */
        G->vertex[i].firstarc = p;
        /** i为入边，j为出边，创建邻接表 */
        p = (ArcNode*)malloc(sizeof(ArcNode));
        assert(p);
        p->adjvex = i;
        p->info = NULL;
        p->nextarc = G->vertex[j].firstarc;
        G->vertex[j].firstarc = p;
    }
    
    (*G).kind = UG;
}
/** 销毁无向图 */
void DestroyGraph(AdjGraph * G)
{
    int i;
    ArcNode * p, * q;
    for (i = 0; i < (*G).vexnum; i++) { /** 释放图中的边表结点 */
        p = G->vertex[i].firstarc;      /** p 指向边表的第一个结点 */
        if (p != NULL) {
            q = p->nextarc;
            free(p);
            p = q;
        }
    }
    (*G).vexnum = 0;
    (*G).arcnum = 0;
}
/** 图的邻接表存储结构的输出 */
void DisplayGraph(AdjGraph G)
{
    int i;
    ArcNode * p;
    
    printf("%d个顶点:\n", G.vexnum);
    for (i = 0; i < G.vexnum; i++) {
        printf("%s ", G.vertex[i].data);
    }
    
    printf("\n%d条边:\n", 2 * G.arcnum);
    for (i = 0; i < G.vexnum; i++) {
        p = G.vertex[i].firstarc;   /** p 指向边表的第一个结点 */
        while (p) {
            printf("%s->%s ", G.vertex[i].data, G.vertex[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
}

/**
    测试:
    
    采用邻接表创建无向图G: 
    请输入图的顶点数，边数(逗号分隔): 5, 4
    请输入5个顶点的值:
    a b c d e
    请输入弧尾和弧头(以空格作为间隔):
    a b
    b c
    c a
    d c
    输出无向图G: 5个顶点:
    a b c d e 
    8条边:
    a->c a->b 
    b->c b->a 
    c->d c->a c->b 
    d->c 

 */

int main()
{
    AdjGraph G;
    
    printf("采用邻接表创建无向图G: \n");
    CreateGraph(&G);
    
    printf("输出无向图G: ");
    DisplayGraph(G);
    
    DestroyGraph(&G);
    
    return 0;
}