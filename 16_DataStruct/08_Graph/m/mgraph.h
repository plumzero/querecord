
// 仅作测试用，不考虑输入异常情况

// 邻接矩阵实现

// 无向图

#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <algorithm>

typedef struct VNode {
    int val;
} VNode;

typedef struct MGraph {
    std::vector<VNode*> vertex;         // 顶点信息
    std::vector<std::vector<int>> arc;  // 顶点之间的关系。无向图中，若顶点与顶点之间有关联，则为 1，否则为 0
} MGraph;

int locate(MGraph& graph, VNode* node)
{
    std::vector<VNode*> vec = graph.vertex;
    auto it = std::find_if(vec.begin(), vec.end(), [node](const VNode* ele){ return ele == node; });
    if (it == vec.end())
        return -1;
    else
        return std::distance(vec.begin(), it);
}

VNode* add_vertex(MGraph& graph, int val)
{
    VNode* node = new VNode();
    node->val = val;
    graph.vertex.push_back(node);

    return node;
}

void init_matrix(MGraph& graph)
{
    size_t len = graph.vertex.size();
    auto & arc = graph.arc;
    arc.resize(len);
    for (size_t i = 0; i < len; i++) {
        arc[i].resize(len);
    }
}

void add_arc(MGraph& graph, VNode* node, VNode* adj)
{
    int i = locate(graph, node);
    int j = locate(graph, adj);

    auto & arc = graph.arc;
    arc[i][j] = 1;
    arc[j][i] = 1;
}

void destroy(MGraph& graph)
{
    std::vector<VNode*> vec = graph.vertex;
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] != nullptr) {
            delete vec[i];
            vec[i] = nullptr;
        }
    }
    vec.clear();

    auto & arc = graph.arc;
    for (size_t i = 0; i < arc.size(); i++) {
        arc[i].clear();
    }
    arc.clear();
}

void display(MGraph& graph)
{
    auto & vec = graph.vertex;
    auto & arc = graph.arc;
    // 只从上三角矩阵(排除对角线)中寻找
    for (size_t i = 0; i < vec.size(); i++) {
        for (size_t j = i + 1; j < vec.size(); j++) {
            if (arc[i][j] == 1) {
                printf("%d-%d ", vec[i]->val, vec[j]->val);
            }
        }
        printf("\n");
    }
}