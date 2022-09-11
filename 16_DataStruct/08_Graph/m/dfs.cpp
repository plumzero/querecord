
// 利用邻接矩阵进行深度优先遍历

#include <stdio.h>

#include "mgraph.h"

#include <stack>

void dfs(MGraph& graph, VNode* start)
{
    std::vector<VNode*> vec = graph.vertex;
    auto & arc = graph.arc;
    std::stack<VNode*> _stack;
    std::vector<int> _visited(graph.vertex.size(), 0);
    int i, j;

    _stack.push(start);
    i = locate(graph, start);
    _visited[i] = 1;
    printf("%d ", start->val);

    while (_stack.size() > 0) {
        VNode* node = _stack.top();
        i = locate(graph, node);
        for (j = 0; j < vec.size(); j++) {
            if (arc[i][j] == 1 && _visited[j] == 0) {
                _stack.push(vec[j]);
                _visited[j] = 1;
                printf("%d ", vec[j]->val);
                break;
            }
        }
        if (j == vec.size()) {
            _stack.pop();
        }
    }
    printf("\n");
}

// 	   1
//  /  \  \
// 2    3  4
//  \     / \
//   5   6   7
//  / \ / \
// 8   9   10

int main()
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

    dfs(G, node2);

    destroy(G);


    return 0;
}
