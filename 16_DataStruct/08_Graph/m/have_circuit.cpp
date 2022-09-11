
// 判断有向图中是否存在回路，若有，则输出这样的一条回路

// 类似的问题有 判断有向图中是否有根顶点。
// 说明: 在有向图中，如果顶点 r 到图中每个顶点都有路径可达，则称顶点 r 为该有向图的根顶点。

#include "dimgraph.h"

#include <stdio.h>
#include <vector>

bool _have_circuit(MGraph& graph, VNode* node);

// 分别从每个顶点出发，进行深度优先遍历
bool have_circuit(MGraph& graph)
{
    std::vector<VNode*> vec = graph.vertex;
    for (size_t i = 0; i < vec.size(); i++) {
        bool have = _have_circuit(graph, vec[i]);
        if (have) {
            return true;
        }
    }

    return false;
}

// 在深度优先遍历的基础上修改
bool _have_circuit(MGraph& graph, VNode* start)
{
    std::vector<VNode*> vec = graph.vertex;
    auto & arc = graph.arc;
    std::vector<VNode*> _stack;
    std::vector<int> _visited(graph.vertex.size(), 0);
    int i, j;

    _stack.push_back(start);
    i = locate(graph, start);
    _visited[i] = 1;

    while (_stack.size() > 0) {
        VNode* node = _stack.back();
        i = locate(graph, node);
        for (j = 0; j < vec.size(); j++) {
            if (arc[i][j] == 1) {
                if (vec[j] == start) {
                    for (size_t k = 0; k < _stack.size(); k++) {
                        printf("%d -> ", _stack[k]->val);
                    }
                    printf("%d\n", _stack[0]->val);
                    return true;
                } else if (_visited[j] == 0) {
                    _stack.push_back(vec[j]);
                    _visited[j] = 1;
                    break;
                }
            }
        }
        if (j == vec.size()) {
            _stack.pop_back();
        }
    }
    
    return false;
}

int main()
{
    {
        MGraph G;

        VNode* node1 = add_vertex(G, 1);
        VNode* node2 = add_vertex(G, 2);
        VNode* node3 = add_vertex(G, 3);
        VNode* node4 = add_vertex(G, 4);

        init_matrix(G);

        add_arc(G, node1, node2);
        add_arc(G, node1, node3);
        add_arc(G, node2, node3);
        add_arc(G, node2, node4);
        add_arc(G, node4, node1);

        printf("%s\n", have_circuit(G) ? "" : "no have");

        destroy(G);
    }

    {
        MGraph G;

        VNode* node1 = add_vertex(G, 1);
        VNode* node2 = add_vertex(G, 2);
        VNode* node3 = add_vertex(G, 3);
        VNode* node4 = add_vertex(G, 4);
        VNode* node5 = add_vertex(G, 5);
        VNode* node6 = add_vertex(G, 6);
        VNode* node7 = add_vertex(G, 7);
        VNode* node8 = add_vertex(G, 8);
        VNode* node9 = add_vertex(G, 9);
        VNode* nodex = add_vertex(G, 10);

        init_matrix(G);

        add_arc(G, node1, node2);
        add_arc(G, node1, node3);
        add_arc(G, node1, node4);
        add_arc(G, node2, node5);
        add_arc(G, node4, node6);
        add_arc(G, node4, node7);
        add_arc(G, node5, node8);
        add_arc(G, node5, node9);
        add_arc(G, node6, node9);
        add_arc(G, node6, nodex);

        printf("%s\n", have_circuit(G) ? "" : "no have");

        destroy(G);
    }

    return 0;
}