
#include "wgraph.h"

int main()
{
    Graph G;
    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);

    add_arc(G, node1, node2, 1);
    add_arc(G, node1, node5, 2);
    add_arc(G, node2, node3, 3);
    add_arc(G, node2, node4, 1);
    add_arc(G, node3, node4, 2);
    add_arc(G, node3, node5, 4);
    add_arc(G, node4, node5, 1);

    display(G);

    printf("node1 node5: %d\n", get_weight(G, node1, node5));
    printf("node3 node5: %d\n", get_weight(G, node3, node5));

    destroy(G);

    return 0;
}