
#include "mgraph.h"
#include <vector>
#include <map>

/** 利用 Kruskal 算法构造无向网 G 的最小生成树 */
void Kruskal(MGraph G)
{
    std::vector<int> sets;  /** 顶点到集合的映射，下标为顶点，值为映射集合编号(实际并不存在) */
    std::multimap<VRType, std::pair<int, int>> edges;
    int i, j, k;
    
    for (i = 0; i < G.vex.size(); i++) {
        sets.push_back(i);
    }
    
    for (i = 0; i < G.vex.size(); i++) {    /** 矩阵上三角获得所有边及对应权值 */
        for (j = i + 1; j < G.vex.size(); j++) {
            edges.emplace(G.arc[i][j].adj, std::pair<int, int>(i, j));  /** 缺省排序 */
        }
    }
    
    while (! edges.empty()) {
        auto iter = edges.begin();
        if (sets[iter->second.first] != sets[iter->second.second]) {
            
            printf("(%s-%s)=%lu\n", G.vex[iter->second.first].name.c_str(), G.vex[iter->second.second].name.c_str(), iter->first);
            
            int ou = sets[iter->second.second];     /** 记下旧的集合 */
            for (i = 0; i < sets.size(); i++) {     /** 合并集合 */
                if (sets[i] == ou) {
                    sets[i] = sets[iter->second.first];
                }
            }
        }
        edges.erase(iter);  
    }
}

int main()
{
    MGraph G;
    
    printf("创建无向网:\n");
    CreateGraph(&G, UN);
    
    printf("输入图的信息:\n");
    VertexType va = { .name = "A" };
    VertexType vb = { .name = "B" };
    VertexType vc = { .name = "C" };
    VertexType vd = { .name = "D" };
    VertexType ve = { .name = "E" };
    
    // 创建顶点信息
    InsertVertex(&G, va);
    InsertVertex(&G, vb);
    InsertVertex(&G, vc);
    InsertVertex(&G, vd);
    InsertVertex(&G, ve);
    
    // 创建弧或边信息
    InsertArc(&G, "A", "B", 6);
    InsertArc(&G, "A", "D", 7);
    InsertArc(&G, "A", "E", 12);
    InsertArc(&G, "B", "C", 8);
    InsertArc(&G, "B", "E", 9);
    InsertArc(&G, "C", "D", 6);
    InsertArc(&G, "C", "E", 4);
    InsertArc(&G, "D", "E", 5);
    
    printf("输出图的顶点和边:\n");
    DisplayGraph(G);
    
    Kruskal(G);
    
    printf("销毁图:\n");
    DestroyGraph(&G);
    
    return 0;
}