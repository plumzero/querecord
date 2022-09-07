
#include "graph.h"

int main()
{
    Graph G;
    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);

    add_arc(G, node1, node2);
    add_arc(G, node1, node5);
    add_arc(G, node2, node1);
    add_arc(G, node2, node3);
    add_arc(G, node2, node4);
    add_arc(G, node3, node2);
    add_arc(G, node3, node4);
    add_arc(G, node3, node5);
    add_arc(G, node4, node2);
    add_arc(G, node4, node3);
    add_arc(G, node4, node5);
    add_arc(G, node5, node1);
    add_arc(G, node5, node3);
    add_arc(G, node5, node4);

    display(G);

    destroy(G);

    return 0;
}