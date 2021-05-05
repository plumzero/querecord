
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * 邻接矩阵表示
 */

typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;

#define INFINITY    -1          /** 定义一个无限大的值 */
#define MAXSIZE     100         /** 最大顶点个数 */
typedef enum {
    DG,         // 有向图
    DN,         // 有向网
    UG,         // 无向图
    UN          // 无向网
} GraphKind;

typedef struct {
    VRType adj;     /** 对于无权图，用 1 表示相邻，0 表示不相邻；对于带权图，存储权值 */
    InfoPtr * info; /** 与弧或边相关的信息 */
} ArcNode;

typedef ArcNode AdjMatrix[MAXSIZE][MAXSIZE];

/** 图的类型定义 */
typedef struct {
    VertexType vex[MAXSIZE];    /** 用于存储顶点 */
    AdjMatrix arc;              /** 邻接矩阵，存储边或弧的信息 */
    int vexnum, arcnum;         /** 顶点数和边(弧)的数目 */
    GraphKind kind;             /** 图的类型 */
} MGraph;

/**
 * 采用邻接矩阵创建一个有向网
 */

/** 在顶点向量中查找顶点 v，找到返回在向量的序号，否则返回 -1 */
int LocateVertex(MGraph N, VertexType v)
{
    int i;
    for (i = 0; i < N.vexnum; i++) {
        if (strcmp(N.vex[i], v) == 0) {
            return i;
        }
    }
    
    return -1;
}
/** 创建有向网 */
void CreateGraph(MGraph * N)
{
    int i, j, k, w, InfoFlag, len;
    char s[MAXSIZE];
    VertexType v1, v2;
    
    printf("请输入有向网N的顶点数，弧数，弧的信息(是:1,否:0): ");
    scanf("%d,%d,%d", &(*N).vexnum, &(*N).arcnum, &InfoFlag);
    
    printf("请输入%d个顶点的值(<%d个字符):\n", N->vexnum, MAXSIZE);
    for (i = 0; i < N->vexnum; i++) {   /** 创建一个数组，用于保存网的各个顶点 */
        scanf("%s", N->vex[i]);
    }
    for (i = 0; i < N->vexnum; i++) {
        for (j = 0; j < N->vexnum; j++) {
            N->arc[i][j].adj = INFINITY;
            N->arc[i][j].info = NULL;
        }
    }
    
    printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔):\n", N->arcnum);
    for (k = 0; k < N->arcnum; k++) {
        scanf("%s%s%d", v1, v2, &w);        /** 输入两个顶点和弧的权值 */
        i = LocateVertex(*N, v1);
        j = LocateVertex(*N, v2);
        N->arc[i][j].adj = w;
        if (InfoFlag) {
            printf("请输入弧的相关信息: ");
            fgets(s, sizeof(s), stdin);
            len = strlen(s);
            if (len) {
                N->arc[i][j].info = (char*)malloc((len + 1) * sizeof(char));
                strcpy(N->arc[i][j].info, s);
            }
        }
    }
    
    N->kind = DN;
}
/** 销毁网 */
void DestroyGraph(MGraph * N)
{
    int i, j;
    for (i = 0; i < N->vexnum; i++) {
        for (j = 0; j < N->vexnum; j++) {
            if (N->arc[i][j].adj != INFINITY) { /** 如果存在弧 */
                if (N->arc[i][j].info != NULL) {
                    free(N->arc[i][j].info);
                    N->arc[i][j].info = NULL;
                }
            }
        }
    }
    
    N->vexnum = 0;
    N->arcnum = 0;
}

/** 输出邻接矩阵存储表示的图 */
void DisplayGraph(MGraph N)
{
    int i, j;
    
    printf("有向网具有 %d 个顶点 %d 条弧，顶点依次是: ", N.vexnum, N.arcnum);
    for (i = 0; i < N.vexnum; i++) {    /** 输出网的顶点 */
        printf("%s ", N.vex[i]);
    }
    printf("\n有向网N的:\n");
    printf("序号i=");
    for (i = 0; i < N.vexnum; i++) {
        printf("%8d", i);
    }
    printf("\n");
    
    for (i = 0; i < N.vexnum; i++) {
        printf("%8d", i);
        for (j = 0; j < N.vexnum; j++) {
            printf("%8d", N.arc[i][j].adj);
        }
        printf("\n");
    }
}

/**
    测试示例

    创建一个网:
    请输入有向网N的顶点数，弧数，弧的信息(是:1,否:0): 5，^H^C
    [root@localhost 0904]# ./test
    创建一个网:
    请输入有向网N的顶点数，弧数，弧的信息(是:1,否:0): 5,6,0
    请输入5个顶点的值(<100个字符):
    A B C D E
    请输入6条弧的弧尾 弧头 权值(以空格作为间隔):
    A B 3
    B C 6
    C D 9
    A D 12
    D E 23
    D A 13
    输出网的顶点和弧:
    有向网具有 5 个顶点 6 条弧，顶点依次是: A B C D E 
    有向网N的:
    序号i=       0       1       2       3       4
           0      -1       3      -1      12      -1
           1      -1      -1       6      -1      -1
           2      -1      -1      -1       9      -1
           3      13      -1      -1      -1      23
           4      -1      -1      -1      -1      -1
    销毁网:
 */
int main()
{
    MGraph N;
    
    printf("创建一个网:\n");
    CreateGraph(&N);
    
    printf("输出网的顶点和弧:\n");
    DisplayGraph(N);
    
    printf("销毁网:\n");
    DestroyGraph(&N);
    
    return 0;
}