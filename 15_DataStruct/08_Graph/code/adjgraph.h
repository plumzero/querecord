
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string>
#include <algorithm>

/**
 * 邻接表基本操作
 *
 * 注意: 这里是在栈上创建图
 */

typedef enum {
    DG,     // 有向图
    DN,     // 有向网
    UG,     // 无向图
    UN      // 无向网
} GraphKind;

typedef int VRType;

/** 弧(边)结点 */
struct ArcNode {
    VRType adjvex;              /** 弧(边)指向的顶点的位置 */
    struct ArcNode * nextarc;   /** 指示下一个与该顶点相邻接的顶点 */
    // void * info;             /** 与弧(边)相关的信息 */
    int weight;           /** 权 */
    ArcNode() : nextarc(nullptr) {}
};

/** 顶点结点 */
struct VNode {
    std::string name;           /** 名称 */
    ArcNode * firstarc;         /** 指示第一个与该顶点邻接的顶点(该顶点的一条边或弧) */
    // void * info;             /** 顶点结点相关的信息 */
    
    VNode() : firstarc(nullptr) {}
    VNode(const std::string& n) : name(n), firstarc(nullptr) {}
    
};

struct AdjGraph {
    std::vector<VNode> vertex;  /** 顶点列表 */
    int arcnum;                 /** 弧(边)数目 */
    GraphKind kind;             /** 图的类型 */
};

/** 创建图。(缺省时创建有向图) */
void CreateGraph(AdjGraph * G, GraphKind kind = DG)
{
    G->vertex.clear();
    G->arcnum = 0;
    G->kind = kind;
}

/** 销毁图。 */
void DestroyGraph(AdjGraph * G)
{
    ArcNode * p, * q;
    
    size_t i;
    for (i = 0; i < G->vertex.size(); i++) {
        p = G->vertex[i].firstarc;
        while (p != nullptr) {
            q = p->nextarc;
            free(p);
            p = q;
        }
    }
    
    G->arcnum = 0;
}

/** 定位顶点位置。 */
int LocateVertex(AdjGraph G, const std::string& name)
{
    auto it = std::find_if(G.vertex.begin(), G.vertex.end(), [name](const VNode& e) {
        return e.name == name;
    });
    if (it != G.vertex.end()) {
        return std::distance(G.vertex.begin(), it);
    }
    
    return -1;
}

/** 增加新的顶点。(如果顶点名称已经存在，则替换相关信息。) */
void InsertVertex(AdjGraph * G, const VNode& v)
{
    auto it = std::find_if(G->vertex.begin(), G->vertex.end(), [v](const VNode& e) {
        return e.name == v.name;
    });
    
    if (it != G->vertex.end()) {
        // 如果顶点名称已经存在，则替换相关信息。
    } else {
        G->vertex.push_back(v);
    }
}

/** 增加边(及边的信息)。 */
int InsertArc(AdjGraph * G, const std::string& vname, const std::string& wname, size_t weight = 0)
{
    int vi = LocateVertex(*G, vname);
    int wi = LocateVertex(*G, wname);
    if (vi < 0 || wi < 0) {
        return -1;
    }
    
    ArcNode * p;
    
    p = (ArcNode*)calloc(1, sizeof(ArcNode));
    assert(p);
    p->adjvex = wi;
    p->nextarc = G->vertex[vi].firstarc;
    p->weight = weight;
    G->vertex[vi].firstarc = p;
        
    G->arcnum++;
    
    if (G->kind == UG || G->kind == UN) {
        p = (ArcNode*)calloc(1, sizeof(ArcNode));
        assert(p);
        p->adjvex = vi;
        p->nextarc = G->vertex[wi].firstarc;
        p->weight = weight;
        G->vertex[wi].firstarc = p; 
    }
        
    return 0;
}

/** 图的邻接表存储结构的输出 */
void DisplayGraph(AdjGraph G)
{
    size_t i;
    ArcNode * p;
    
    printf("图具有 %lu 个顶点, %d 条弧(边)\n", G.vertex.size(), G.arcnum);
    
    for (i = 0; i < G.vertex.size(); i++) {    /** 输出图的顶点 */
        printf("%s ", G.vertex[i].name.c_str());
    }
    printf("\n");
    
    for (i = 0; i < G.vertex.size(); i++) {
        p = G.vertex[i].firstarc;   /** p 指向边表的第一个结点 */
        printf("%-4s: ", G.vertex[i].name.c_str());
        while (p) {
            printf("%s->%s ", G.vertex[i].name.c_str(), G.vertex[p->adjvex].name.c_str());
            p = p->nextarc;
        }
        printf("\n");
    }
}

/** 返回顶点 v 的第一个邻接顶点的序号 */
int FirstAdjVertex(AdjGraph G, const std::string& name)
{
    ArcNode * p;
    int vi;
    
    vi = LocateVertex(G, name);
    p = G.vertex[vi].firstarc;
    if (p)
        return p->adjvex;
    else
        return -1;
}

/** 返回 v 的相对于 w 的下一个邻接顶点的序号 */
int NextAdjVertex(AdjGraph G, const std::string& vname, const std::string& wname)
{
    ArcNode * p, * next;
    
    int vi = LocateVertex(G, vname);
    int wi = LocateVertex(G, wname);
    
    for (next = G.vertex[vi].firstarc; next; ) {
        if (next->adjvex != wi) {
            next = next->nextarc;
        } else {
            break;
        }
    }
    
    p = next;
    if (!p || !p->nextarc) {
        return -1;
    } else {
        return p->nextarc->adjvex;
    }
}

static void Visit(const VNode& v)
{
    printf("%s ", v.name.c_str());
}

void DFS(AdjGraph G, int vi, std::vector<int>* visited)
{
    int wi;
    
    visited->at(vi) = 1;

    // printf("%s ", G.vertex[vi].name.c_str());
    Visit(G.vertex[vi]);
    
    for (wi = FirstAdjVertex(G, G.vertex[vi].name); wi >= 0; wi = NextAdjVertex(G, G.vertex[vi].name, G.vertex[wi].name)) {
        if (visited->at(wi) == 0) {
            DFS(G, wi, visited);
        }
    }
}

/** 深度优先遍历图 */
void DFSTraverseGraph(AdjGraph G)
{
    std::vector<int> visited;
    visited.resize(G.vertex.size());
    
    size_t vi;
    for (vi = 0; vi < G.vertex.size(); vi++) {
        if (! visited[vi]) {
            DFS(G, vi, &visited);
        }
    }
}

/** 广度优先遍历 */
void BFSTraverseGraph(AdjGraph G)
{   
    int vi, front, rear;
    ArcNode * p;
    std::vector<int> queue;
    std::vector<int> visited;
    
    queue.resize(5);
    visited.resize(G.vertex.size());
    
    front = rear = -1;
    
    vi = 0;
    visited[vi] = 1;
    Visit(G.vertex[vi]);
    
    rear = (rear + 1) % queue.size();
    queue[rear] = vi;
    
    while (front != rear) {
        front = (front + 1) % queue.size();
        vi = queue[front];
        p = G.vertex[vi].firstarc;
        while (p) {
            if (! visited[p->adjvex]) {
                visited[p->adjvex] = 1;
                Visit(G.vertex[p->adjvex]);
                rear = (rear + 1) % queue.size();
                queue[rear] = p->adjvex;
            }
            p = p->nextarc;
        }
    }
}