
#include "mgraph.h"
#include <assert.h>

void Floyd(MGraph G, std::vector<std::vector<std::vector<int>>>& path, std::vector<std::vector<int>>& dist)
{
    size_t v, w, u, i, j;   /** 要理解 v, w, u 的含义 */
    
    /** 调整矩阵 */
    path.resize(G.vex.size());
    for (i = 0; i < path.size(); i++) {
        path[i].resize(G.vex.size());
    }
    for (i = 0; i < path.size(); i++) {
        for (j = 0; j < path[i].size(); j++) {
            path[i][j].resize(G.vex.size());
        }
    }
    dist.resize(G.vex.size());
    for (i = 0; i < dist.size(); i++) {
        dist[i].resize(G.vex.size());
    }
    
    /** 初始化 */
    for (v = 0; v < G.vex.size(); v++) {
        for (w = 0; w < G.vex.size(); w++) {
            /** 存储顶点 v 到顶点 w 的最短路径，初始化为 <v,w> 的权值 */
            dist[v][w] = (v != w ? G.arc[v][w].adj : 0);
            for (u = 0; u < G.vex.size(); u++) {
                path[v][w][u] = 0;          /** 表示由 v 到 w 的路径是否经过 u。初始化为 0 */
            }
            /** 如果 v 到 w 有直接路径，则由 v 到 w 很明显必经过 v 和 w 两点 */
            if (dist[v][w] < INFINITY_MAX) {
                path[v][w][v] = 1;
                path[v][w][w] = 1;
            }
        }
    }
    
    for (u = 0; u < G.vex.size(); u++) {
        for (v = 0; v < G.vex.size(); v++) {
            for (w = 0; w < G.vex.size(); w++) {
                /**
                 * 如果 v 到 u 存在一条路径，且 u 到 w 存在一条路径，且 <v,...,u> 和 <u,...,w> 的路径
                 * 之和比之前记录的 <v,...,w> 要小，则进行更新
                 */
                if (dist[v][u] < INFINITY_MAX && dist[u][w] < INFINITY_MAX &&
                    dist[v][u] + dist[u][w] < dist[v][w])
                {
                    printf("v=%lu, w=%lu, u=%lu\n", v, w, u);
                    dist[v][w] = dist[v][u] + dist[u][w];
                    /** 从 v 到 w 的路径经过从 v 到 u 和从 u 到 w 的所有路径。尝试意会吧... */
                    for (i = 0; i < G.vex.size(); i++) {
                        path[v][w][i] = path[v][u][i] || path[u][w][i];
                    }
                }
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
    VertexType v0 = { .name = "V0" };
    VertexType v1 = { .name = "V1" };
    VertexType v2 = { .name = "V2" };
    VertexType v3 = { .name = "V3" };
    VertexType v4 = { .name = "V4" };
    VertexType v5 = { .name = "V5" };
    
    // 创建顶点信息
    InsertVertex(&G, v0);
    InsertVertex(&G, v1);
    InsertVertex(&G, v2);
    InsertVertex(&G, v3);
    InsertVertex(&G, v4);
    InsertVertex(&G, v5);
    
    // 创建弧或边信息
    InsertArc(&G, "V0", "V1", 30);
    InsertArc(&G, "V0", "V2", 60);
    InsertArc(&G, "V0", "V4", 150);
    InsertArc(&G, "V0", "V5", 40);
    InsertArc(&G, "V1", "V2", 40);
    InsertArc(&G, "V1", "V3", 100);
    InsertArc(&G, "V2", "V3", 50);
    InsertArc(&G, "V3", "V4", 30);
    InsertArc(&G, "V4", "V5", 10);
    
    printf("输出图的顶点和弧:\n");
    DisplayGraph(G);
    
    std::vector<std::vector<std::vector<int>>> path;
    std::vector<std::vector<int>> dist;
    printf("Floyd 算法求每一对顶点之间的最短路径:\n");
    Floyd(G, path, dist);

    size_t v, w, u;
    printf("顶点之间的最短路径长度矩阵 dist:\n");
    for (v = 0; v < G.vex.size(); v++) {
        for (w = 0; w < G.vex.size(); w++) {
            printf("%6d", dist[v][w]);
        }
        printf("\n");
    }
    
    for (v = 0; v < G.vex.size(); v++) {
        for (w = 0; w < G.vex.size(); w++) {
            if (v != w) {
                printf("%s 到 %s 的最短路径为 %d\n", G.vex[v].name.c_str(), G.vex[w].name.c_str(), dist[v][w]);
            }
        }
    }
    
    printf("各顶点之间的最短路径所经过的顶点:\n");
    for (v = 0; v < G.vex.size(); v++) {
        for (w = 0; w < G.vex.size(); w++) {
            if (v != w) {
                printf("由 %s 到 %s 经过: ", G.vex[v].name.c_str(), G.vex[w].name.c_str());
                for (u = 0; u < G.vex.size(); u++) {
                    if (path[v][w][u] == 1) {
                        printf("%s ", G.vex[u].name.c_str());
                    }
                }
                printf("\n");
            }
        }
    }
    
    printf("销毁图:\n");
    DestroyGraph(&G);
    
	printf("=== %lu\n", INFINITY);
	
    return 0;
}