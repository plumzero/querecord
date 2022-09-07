
#include "wgraph.h"

#include <vector>
#include <map>

void kruskal(Graph& graph)
{
    std::multimap<int, std::pair<VNode*, VNode*>> _map;  // 键为权重

    std::vector<VNode*> vec = graph.vertex;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        VNode* node = *it;

    }
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

    add_arc(G, node1, node2, 6);
    add_arc(G, node1, node5, 10);
    add_arc(G, node1, node6, 12);
    add_arc(G, node2, node3, 3);
    add_arc(G, node2, node4, 5);
    add_arc(G, node2, node6, 8);
    add_arc(G, node3, node4, 7);
    add_arc(G, node4, node5, 9);
    add_arc(G, node4, node6, 11);
    add_arc(G, node5, node6, 16);

    display(G);

    bfs(G);

    destroy(G);

    return 0;
}