
#include "mgraph.h"

int main()
{
    MGraph G;

    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);

    init_matrix(G);

    add_arc(G, node1, node2);
    add_arc(G, node1, node4);
    add_arc(G, node1, node5);
    add_arc(G, node2, node3);
    add_arc(G, node3, node4);
    add_arc(G, node3, node5);
    add_arc(G, node4, node5);

    display(G);

    destroy(G);

    return 0;
}