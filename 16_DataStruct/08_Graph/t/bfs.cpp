
// 图的广度优先遍历

#include "graph.h"

#include <queue>
#include <vector>

//         1
//     /    \   \
//    2      3   4
//    \     /   / \
//     5 — 6   7 — 8
//             \
//              9

void bfs(Graph& graph)
{
    std::queue<VNode*> _queue;
    std::vector<int> _visited(graph.vertex.size());
    for (size_t i = 0; i < _visited.size(); i++) {
        _visited[i] = 0;
    }

    std::vector<VNode*> vec = graph.vertex;

    _queue.push(vec[0]);

    while (_queue.size() > 0) {
        VNode* node = _queue.front();
        _queue.pop();
        int pos = locate(graph, node);
        _visited[pos] = 1;
        printf("%d ", node->val);
        ArcNode* cur = node->firstarc;
        while (cur != nullptr && _visited[cur->pos] == 1) {
            cur = cur->nextarc;
        }
        while (cur) {
            _queue.push(vec[cur->pos]);
            cur = cur->nextarc;
        }
    }
    printf("\n");
}

int main()
{
    Graph G;
    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);
    VNode* node6 = add_vertex(G, 6);
    VNode* node7 = add_vertex(G, 7);
    VNode* node8 = add_vertex(G, 8);
    VNode* node9 = add_vertex(G, 9);

    add_arc(G, node1, node2);
    add_arc(G, node1, node3);
    add_arc(G, node1, node4);
    add_arc(G, node2, node1);
    add_arc(G, node2, node5);
    add_arc(G, node3, node1);
    add_arc(G, node3, node6);
    add_arc(G, node4, node1);
    add_arc(G, node4, node7);
    add_arc(G, node4, node8);
    add_arc(G, node5, node2);
    add_arc(G, node5, node6);
    add_arc(G, node6, node3);
    add_arc(G, node6, node5);
    add_arc(G, node7, node4);
    add_arc(G, node7, node8);
    add_arc(G, node7, node9);
    add_arc(G, node8, node4);
    add_arc(G, node8, node7);
    add_arc(G, node9, node7);

    display(G);

    bfs(G);

    destroy(G);

    return 0;
}