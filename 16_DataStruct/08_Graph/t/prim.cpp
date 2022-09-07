
// prim 算法构造最小生成树

#include "wgraph.h"

#include <set>
#include <limits.h>

void prim(Graph& graph)
{
    std::set<VNode*> _u;    // U
    std::set<VNode*> _v_u;  // V - U

    std::vector<VNode*> vec = graph.vertex;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        _v_u.insert(*it);
    }

    _v_u.erase(vec[0]);
    _u.insert(vec[0]);

    int pos, upos;
    
    while (_v_u.size() > 0) {
        int min_weight = INT_MAX;
        for (auto it = _v_u.begin(); it != _v_u.end(); it++) {
            VNode* node = *it;
            ArcNode* cur = node->firstarc;
            while (cur != nullptr) {
                if (_u.find(vec[cur->pos]) != _u.end()) {
                    int weight = get_weight(graph, node, vec[cur->pos]);
                    if (min_weight > weight) {
                        min_weight = weight;
                        pos = locate(graph, node);
                        upos = cur->pos;
                    }
                }
                cur = cur->nextarc;
            }
        }

        printf("%d-%d(%d)\n", vec[pos]->val, vec[upos]->val, min_weight);
        
        _v_u.erase(vec[pos]);
        _u.insert(vec[pos]);
    }
}



//  1  -   2
//    \  /   \
//     6   |  3
//   /   \   /
//  5 -    4

int main()
{
    Graph G;
    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);
    VNode* node6 = add_vertex(G, 6);

    add_arc(G, node1, node2, 18);
    add_arc(G, node1, node5, 12);
    add_arc(G, node1, node6, 15);
    add_arc(G, node2, node3, 8);
    add_arc(G, node2, node4, 10);
    add_arc(G, node2, node6, 26);
    add_arc(G, node3, node4, 6);
    add_arc(G, node4, node5, 15);
    add_arc(G, node4, node6, 23);
    add_arc(G, node5, node6, 12);

    display(G);

    prim(G);

    destroy(G);

    return 0;
}