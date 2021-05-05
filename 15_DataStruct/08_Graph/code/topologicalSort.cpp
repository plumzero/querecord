
#include "adjgraph.h"
#include <vector>
#include <stack>

int TopologicalSort(AdjGraph G)
{
    int i, k, count = 0;
    std::vector<int> indegrees;
    std::stack<int> sk;
    ArcNode * p;
    
    indegrees.resize(G.vertex.size());
    
    /** 图中各顶点入度存入数组 */
    for (i = 0; i < G.vertex.size(); i++) {
        p = G.vertex[i].firstarc;
        while (p) {
            k = p->adjvex;
            indegrees[k]++;
            p = p->nextarc;
        }
    }
    
	/** 入度为 0 的顶点入栈 */
    for (i = 0; i < G.vertex.size(); i++) {
        if (indegrees[i] == 0) {
            sk.push(i);
        }
    }
    
    /** 如果栈不空，将栈顶元素出栈，输出该顶点 */
    while (! sk.empty()) {
        i = sk.top();
        sk.pop();
        
        printf("%s ", G.vertex[i].name.c_str());
        
        count++;    /** 输出顶点数加 1 */
        
        /** 处理编号为 i 的顶点的所有邻接顶点 */
        for (p = G.vertex[i].firstarc; p; p = p->nextarc) {
            k = p->adjvex;
            if (--indegrees[k] == 0) {
                sk.push(k);
            }
        }
    }
    
    /** 如果还有未输出的顶点，则存在回路，否则可以构成一个拓扑序列 */
    if (count < G.vertex.size()) {
        printf("\n该有向图存在回路\n");
        return -1;
    } else {
        printf("\n该有向图可以构成一个拓扑序列\n");
        return 0;
    }
}

int main()
{
    AdjGraph G;
        
    printf("创建一个图:\n");
    CreateGraph(&G);
    
    printf("输入图的信息:\n");    
    VNode v1("V1");
    VNode v2("V2");
    VNode v3("V3");
    VNode v4("V4");
    VNode v5("V5");
    VNode v6("V6");
    
    InsertVertex(&G, v1);
    InsertVertex(&G, v2);
    InsertVertex(&G, v3);
    InsertVertex(&G, v4);
    InsertVertex(&G, v5);
    InsertVertex(&G, v6);
    
    InsertArc(&G, "V1", "V2");
    InsertArc(&G, "V1", "V3");
    InsertArc(&G, "V1", "V4");
    InsertArc(&G, "V2", "V4");
    InsertArc(&G, "V3", "V5");
    InsertArc(&G, "V4", "V6");
    InsertArc(&G, "V5", "V4");
    InsertArc(&G, "V5", "V6");
    
    printf("尝试对图进行拓扑排序:\n");
    TopologicalSort(G);
    
    printf("销毁图:\n");
    DestroyGraph(&G);
    
    return 0;
}