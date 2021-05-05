
#include "mgraph.h"
#include <assert.h>

/**
 * vname [in]  从名称为 vname 的顶点出发
 * path: [out] 存储 vname 顶点到各个顶点的路径
 * dist: [out] 最短路径长度
 */
void Dijkstra(MGraph G, const std::string& vname, std::vector<std::vector<int>>& path, std::vector<int>& dist)
{
    size_t vi, wi, i;
    VRType min;
    std::vector<int> S;    /** 集合 S 。用于记录 v0 到索引对应顶点的最短路径是否求出 */
    
    int v0 = LocateVertex(G, vname);
    assert(v0 >= 0);
    
    /** 调整矩阵 */
    path.resize(G.vex.size());
    for (i = 0; i < path.size(); i++) {
        path[i].resize(G.vex.size());
    }
    
    dist.resize(G.vex.size());
    S.resize(G.vex.size());
    
    /** 初始化 */
    for (vi = 0; vi < G.vex.size(); vi++) {
        S[vi] = 0;
        dist[vi] = G.arc[v0][vi].adj;
        for (wi = 0; wi < G.vex.size(); wi++) {
            path[vi][wi] = 0;
        }
        if (dist[vi] < INFINITY_MAX) {    /** 如果从 v0 到 vi 存在直接路径，则利用此路径初始化数组 */
            path[vi][v0] = 1;
            path[vi][vi] = 1;
        }
    }
    
    dist[v0] = 0;   /** v0 到 v0 的路径为 0 */
    S[v0] = 1; /** v0 顶点并入集合 S */
    
    /** 计算从 v0 到其余各顶点的最短路径，并将计算后的顶点并入集合 S */
    for (i = 1; i < G.vex.size(); i++) {    /** 只需要执行 G.vex.size() - 1 次 */
        min = INFINITY_MAX;
        for (wi = 0; wi < G.vex.size(); wi++) {
            if (! S[wi] && dist[wi] < min) {   /** 在不属于 S 的顶点中，找到离 v0 最近的顶点 */
                vi = wi;
                min = dist[wi];
            }
        }
        
        S[vi] = 1;     /** 将顶点 vi 并入到集合 S */
        for (wi = 0; wi < G.vex.size(); wi++) {
            /**
             * 一共有四个判断条件，缺一不可。按这样的顺序进行判断的意义是:
             *  ! S[wi]: 要更新的顶点 wi 应不属于集合 S
             *  min < INFINITY_MAX && G.arc[vi][wi].adj < INFINITY_MAX: 且 v0 到 wi 确实存在一条路径，
             *    其中 min=Min{v0到vi的最短路径}。 min < INFINITY_MAX 说明 v0 到 vi 是存在路径的，
             *    G.arc[vi][wi].adj < INFINITY_MAX 说明 vi 到 wi 也是存在路径的。两者结合说明 v0 到 wi
             *    是存在一条路径的。
             *  min + G.arc[vi][wi].adj < dist[wi]: 这个比较容易理解，就是 v0 通过 vi 点到 wi 的路径长度
             *    如果比原来记录的要小，则替换之。
             */
            if (! S[wi] && 
                min < INFINITY_MAX && G.arc[vi][wi].adj < INFINITY_MAX &&
                (min + G.arc[vi][wi].adj < dist[wi]))
            {
                dist[wi] = min + G.arc[vi][wi].adj;
                /** 更新路径映射，意会意会... */
                for (size_t k = 0; k < G.vex.size(); k++) {
                    path[wi][k] = path[vi][k];
                }
                path[wi][wi] = 1;
            }
        }
    }
}

int main()
{
    MGraph G;
    
    printf("创建有向网:\n");
    CreateGraph(&G);
    
    printf("输入图的信息:\n");
    VertexType va = { .name = "A" };
    VertexType vb = { .name = "B" };
    VertexType vc = { .name = "C" };
    VertexType vd = { .name = "D" };
    VertexType ve = { .name = "E" };
    VertexType vf = { .name = "F" };
    
    // 创建顶点信息
    InsertVertex(&G, va);
    InsertVertex(&G, vb);
    InsertVertex(&G, vc);
    InsertVertex(&G, vd);
    InsertVertex(&G, ve);
    InsertVertex(&G, vf);
    
    // 创建弧或边信息
    InsertArc(&G, "A", "B", 30);
    InsertArc(&G, "A", "C", 60);
    InsertArc(&G, "A", "E", 150);
    InsertArc(&G, "A", "F", 40);
    InsertArc(&G, "B", "C", 40);
    InsertArc(&G, "B", "D", 100);
    InsertArc(&G, "C", "D", 50);
    InsertArc(&G, "D", "E", 30);
    InsertArc(&G, "E", "F", 10);
    
    std::vector<std::vector<int>> path;
    std::vector<int> dist;
    const std::string name = "A";
    printf("Dijkstra 算法求从某个顶点到其余各顶点的最短路径:\n");
    Dijkstra(G, name, path, dist);

    printf("顶点 %s 到各顶点的最短路径长度为:\n", name.c_str());
    int v0 = LocateVertex(G, name);
    for (size_t i = 0; i < G.vex.size(); i++) {
        if ((int)i != v0) {
            printf("%s-%s:%lu\n", G.vex[v0].name.c_str(), G.vex[i].name.c_str(), (size_t)dist[i]);
        }
    }

    printf("顶点 %s(索引=%d)到各个顶点的路径:\n", name.c_str(), v0);
    for (size_t i = 0; i < path.size(); i++) {
        for (size_t j = 0; j < path[i].size(); j++) {
            printf("%d ", path[i][j]);
        }
        printf("\n");
    }

    printf("销毁图:\n");
    DestroyGraph(&G);

    return 0;
}