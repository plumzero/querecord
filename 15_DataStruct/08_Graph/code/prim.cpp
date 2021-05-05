
#include "mgraph.h"
#include <set>

typedef struct {
    std::string adjname;
    VRType lowcost;
} CloseEdge;

/** 利用 prim 算法从名称为 name 的顶点出发构造无向网 G 的最小生成树 */
void Prim(MGraph G, const std::string& name)
{
    int i, j, k;
    std::vector<CloseEdge> ce;
    std::set<int> U, V;
    
    ce.resize(G.vex.size());
    for (i = 0; i < G.vex.size(); i++) {
        V.insert(i);
    }
    
    k =  LocateVertex(G, name);
    U.insert(k);
    V.erase(k);
    for (j = 0; j < G.vex.size(); j++) { /** 初始时，在数组中记录 V-U 中各顶点与 name 顶点的边权 */
        ce[j].adjname = name;
        ce[j].lowcost = G.arc[k][j].adj;
    }
    
    for(i = 1; i < G.vex.size(); i++) { /** i 为比较次数，一共只需要比较 G.vex.size() - 1 次 */
        VRType minCost = (size_t)-1;
        k = -1;
        for (auto it = V.begin(); it != V.end(); it++) {
            if (ce[*it].lowcost < minCost) {
                minCost = ce[*it].lowcost;
                k = *it;
            }
        }
        if (k < 0) {
            return;
        }
        
        printf("(%s-%s)\n", ce[k].adjname.c_str(), G.vex[k].name.c_str());
        
        U.insert(k);
        V.erase(k);
        
        for (auto it = V.begin(); it != V.end(); it++) {
            ce[*it].lowcost = (size_t)-1;
        }
        
        for (auto x = V.begin(); x != V.end(); x++) {
            for (auto y = U.begin(); y != U.end(); y++) {
                if (G.arc[*x][*y].adj < ce[*x].lowcost) {
                    ce[*x].adjname = G.vex[*y].name;
                    ce[*x].lowcost = G.arc[*x][*y].adj;
                }
            }
        }
    }
    
    printf("CloseEdge数组中存储的是:\n");
    for (i = 1; i < ce.size(); i++) {
        printf("%s-%s %d\n", ce[i].adjname.c_str(), G.vex[i].name.c_str(), ce[i].lowcost);
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
    
    Prim(G, "A");
    
    printf("销毁图:\n");
    DestroyGraph(&G);
    
    return 0;
}