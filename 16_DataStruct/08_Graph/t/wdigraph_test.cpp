
#include "wdigraph.h"

int main()
{
    Graph G;
    VNode* node0 = add_vertex(G, 0);
    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);

    add_arc(G, node0, node1, 8);
    add_arc(G, node1, node2, 6);
    add_arc(G, node1, node4, 16);
    add_arc(G, node2, node3, 10);
    add_arc(G, node2, node5, 15);
    add_arc(G, node4, node0, 12);
    add_arc(G, node5, node1, 12);
    add_arc(G, node5, node3, 20);
    add_arc(G, node5, node4, 14);

    display(G);

    destroy(G);

    return 0;
}