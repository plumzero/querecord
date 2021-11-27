
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>

/**
 * 邻接矩阵基本操作
 *
 * 注意: 这里是在栈上创建图
 */

/**
 * 像下面这样定义无穷大定义是错误的
 *   #define INFINITY_MAX ((size_t)-1)
 *   #define INFINITY_MAX ((unsigned int)-1)
 */

#define INFINITY_MAX  140595803510648

typedef enum {
    DG,     // 有向图
    DN,     // 有向网
    UG,     // 无向图
    UN      // 无向网
} GraphKind;

typedef size_t VRType;

/** 顶点 */
typedef struct {
    std::string name;   /** 顶点名称 */
    // void * info;     /** 与顶点相关的信息 */
} VertexType;

struct ArcNode {
    VRType adj;     /** 对于无权图，用 1 表示相邻，0 表示不相邻；对于带权图，存储权值 */
    // void * info; /** 与弧或边相关的信息 */
    
    ArcNode() : adj(INFINITY_MAX) {}
};

/** 图的类型定义 */
typedef struct {
    std::vector<VertexType> vex;    /** 顶点名称 */
    std::vector<std::vector<ArcNode>> arc;
    size_t arcnum;                  /** 为了防止遍历，增加边的记录 */
    GraphKind kind;                 /** 图的类型 */
} MGraph;

/** 创建图。(缺省时创建有向图) */
void CreateGraph(MGraph * G, GraphKind kind = DG)
{    
    G->vex.clear();
    G->arc.clear();
    G->arcnum = 0;
    G->kind = kind;
}

/** 销毁图。 */
void DestroyGraph(MGraph * G)
{        
    G->vex.clear();
    G->arc.clear();
    G->arcnum = 0;    
}

/** 定位顶点位置。 */
int LocateVertex(MGraph G, const std::string& name)
{
    auto it = std::find_if(G.vex.begin(), G.vex.end(), [name](const VertexType& e) {
        return e.name == name;
    });
    if (it != G.vex.end()) {
        return std::distance(G.vex.begin(), it);
    }
    
    return -1;
}

/** 增加新的顶点。(如果顶点名称已经存在，则替换相关信息。) */
void InsertVertex(MGraph * G, const VertexType& v)
{    
    auto it = std::find_if(G->vex.begin(), G->vex.end(), [v](const VertexType& e) {
        return e.name == v.name;
    });
    
    if (it != G->vex.end()) {
        // 如果顶点名称已经存在，则替换相关信息。
    } else {
        G->vex.push_back(v);
        G->arc.resize(G->vex.size());
        size_t i;
        for (i = 0; i < G->arc.size(); i++) {   /** 调整矩阵 */
            G->arc[i].resize(G->vex.size());
        }
    }
}

/** 增加边(及边的信息)。 */
int InsertArc(MGraph * G, const std::string& vname, const std::string& wname, const VRType weight = 1)
{    
    int vi = LocateVertex(*G, vname);
    int wi = LocateVertex(*G, wname);
    if (vi < 0 || wi < 0) {
        return -1;
    }
    
    G->arc[vi][wi].adj = weight;
    // G->arc[vi][wi].info = nullptr;
    G->arcnum++;
    
    if (G->kind == UG || G->kind == UN) {
        G->arc[wi][vi].adj = weight;
        // G->arc[wi][vi].info = nullptr;
    }
    
    return 0;
}

/** 输出邻接矩阵存储表示的图 */
void DisplayGraph(MGraph G)
{
    size_t i, j;
    
    printf("图具有 %lu 个顶点, %lu 条弧\n", G.vex.size(), G.arcnum);
    printf("%16s", "");
    for (i = 0; i < G.vex.size(); i++) {    /** 输出图的顶点 */
        printf("%16s", G.vex[i].name.c_str());
    }
    printf("\n");
    
    for (i = 0; i < G.arc.size(); i++) {
        printf("%16s", G.vex[i].name.c_str());
        for (j = 0; j < G.arc[i].size(); j++) {
            printf("%16lu", G.arc[i][j].adj);
        }
        printf("\n");
    }
}