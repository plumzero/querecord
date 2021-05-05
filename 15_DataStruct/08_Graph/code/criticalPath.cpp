
#include "adjgraph.h"
#include <vector>
#include <stack>

int TopologicalOrder(AdjGraph G, std::vector<int>& ve, std::stack<int>& S)
{
    size_t i, k, count = 0;
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
        
        S.push(i);      /** 入逆拓扑排序栈 */
        
        count++;    /** 输出顶点数加 1 */
        
        /** 处理编号为 i 的顶点的所有邻接顶点 */
        for (p = G.vertex[i].firstarc; p; p = p->nextarc) {
            k = p->adjvex;
            if (--indegrees[k] == 0) {
                sk.push(k);
            }
            
            if (ve[i] + p->weight > ve[k]) {    /** 计算顶点 k 对应的事件的最早发生时间 */
                ve[k] = ve[i] + p->weight;
            }
        }
    }
    
    if (count < G.vertex.size()) {
        return -1;
    } else {
        return 0;
    }
}

int CriticalPath(AdjGraph G)
{
    size_t i, k;
    std::vector<int> ve, vl;
    std::stack<int> sk;
    std::vector<std::pair<int, int>> cripath;    /** 存储关键路径 */
    ArcNode * p;
    
    ve.resize(G.vertex.size());
    vl.resize(G.vertex.size());
    
    if (TopologicalOrder(G, ve, sk) != 0) {
        return -1;
    }

    auto itMax = std::max_element(ve.begin(), ve.end());
    std::fill(vl.begin(), vl.end(), *itMax);
    
    while (! sk.empty()) {
        i = sk.top();
        sk.pop();

        for (p = G.vertex[i].firstarc; p; p = p->nextarc) {
            k = p->adjvex;

            if (vl[k] - p->weight < vl[i]) {    /** 比较取最小,计算事件 i 的最迟发生时间 */
                vl[i] = vl[k] - p->weight;
            }
        }
    }
    
    printf("事件的最早发生时间和最晚发生时间:\n");
    printf("i  ve[i]  vl[i]\n");
    for (i = 0; i < G.vertex.size(); i++) {
        printf("%s   %d    %d\n", G.vertex[i].name.c_str(), ve[i], vl[i]);
    }

    printf("关键路径上的点: ");
    for (i = 0; i < G.vertex.size(); i++) {
        if (ve[i] == vl[i]) {
            printf("%s ", G.vertex[i].name.c_str());
        }
    }
    printf("\n");

    printf("活动的最早开始时间和最晚开始时间:\n");
    printf("  弧     ee   el   el-ee\n");
    for (i = 0; i < G.vertex.size(); i++) {
        for (p = G.vertex[i].firstarc; p; p = p->nextarc) {
            k = p->adjvex;
            int ee = ve[i];             /** ee 就是活动 <i, k> 的最早开始时间 */
            int el = vl[k] - p->weight; /** el 就是活动 <i, k> 的最晚开始时间 */
            printf("%s->%s %4d %4d %4d\n", G.vertex[i].name.c_str(), G.vertex[k].name.c_str(), ee, el, el - ee);
            
            if (ee == el) {
                cripath.emplace_back(std::pair<int, int>(i, k));
            }
        }
    }
    
    printf("关键路径为: ");
    for (i = 0; i < cripath.size(); i++) {
        printf("(%s->%s)", G.vertex[cripath[i].first].name.c_str(), G.vertex[cripath[i].second].name.c_str());
    }
    printf("\n");
    
    return 0;
}

int main()
{
    AdjGraph G;
        
    printf("创建一个网图:\n");
    CreateGraph(&G);
    
    printf("输入图的信息:\n");    
    VNode v1("V1");
    VNode v2("V2");
    VNode v3("V3");
    VNode v4("V4");
    VNode v5("V5");
    VNode v6("V6");
    VNode v7("V7");
    VNode v8("V8");
    
    InsertVertex(&G, v1);
    InsertVertex(&G, v2);
    InsertVertex(&G, v3);
    InsertVertex(&G, v4);
    InsertVertex(&G, v5);
    InsertVertex(&G, v6);
    InsertVertex(&G, v7);
    InsertVertex(&G, v8);
    
    InsertArc(&G, "V1", "V2", 5);
    InsertArc(&G, "V1", "V3", 4);
    InsertArc(&G, "V1", "V4", 6);
    InsertArc(&G, "V2", "V5", 2);
    InsertArc(&G, "V3", "V5", 1);
    InsertArc(&G, "V4", "V7", 3);
    InsertArc(&G, "V5", "V6", 5);
    InsertArc(&G, "V5", "V7", 3);
    InsertArc(&G, "V6", "V8", 4);
    InsertArc(&G, "V7", "V8", 5);
        
    printf("尝试对图寻找关键路径:\n");
    CriticalPath(G);
    
    printf("销毁图:\n");
    DestroyGraph(&G);
    
    return 0;
}