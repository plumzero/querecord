
#include "wdimgraph.h"

int main()
{
    MGraph G;

    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);
    VNode* node6 = add_vertex(G, 6);

    init_matrix(G);

    add_arc(G, node1, node2, 6);
    add_arc(G, node1, node5, 5);
    add_arc(G, node1, node6, 9);
    add_arc(G, node2, node3, 8);
    add_arc(G, node2, node6, 6);
    add_arc(G, node3, node4, 5);
    add_arc(G, node4, node1, 12);
    add_arc(G, node5, node4, 3);
    add_arc(G, node6, node3, 7);

    display(G);

    destroy(G);

    return 0;
}