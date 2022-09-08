
#include "wdigraph.h"

#include <vector>
#include <set>
#include <algorithm>

#include <limits.h>

#define INFINITY_MAX (INT_MAX)

// node 出发的顶点
void dijkstra(Graph& graph, VNode* node)
{
    std::set<VNode*> _s;        // 最短路径上的顶点集合
    std::set<VNode*> _v_s;      // 除最短路径上的顶点的其他顶点集合
    std::vector<int> _dist;

    _s.insert(node);

    std::vector<VNode*> vec = graph.vertex;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        if (*it != node)
            _v_s.insert(*it);
    }

    _dist.resize(vec.size(), INFINITY_MAX);
    for (ArcNode* cur = node->firstarc; cur; cur = cur->nextarc) {
        _dist[cur->pos] = get_weight(graph, node, vec[cur->pos]);
    }

    while (_v_s.size() > 0) {
        int min = INFINITY_MAX;
        VNode* nodex = nullptr;
        // 计算弧 <node,nodex> 的权重
        for (size_t i = 0; i < vec.size(); i++) {
            if (_s.find(vec[i]) == _s.end()) {
                if (min > _dist[i]) {
                    min = _dist[i];
                    nodex = vec[i];
                }
            }
        }
        
        // 计算 _s 集合中每个顶点到 nodex 的距离
        for (auto it = _s.begin(); it != _s.end(); it++) {
            for (ArcNode* cur = (*it)->firstarc; cur; cur = cur->nextarc) {
                if (vec[cur->pos] == nodex) {
                    int pos = locate(graph, *it);
                    // 从 node 到 vec[pos] 存在一条路径
                    if (_dist[pos] < INFINITY_MAX) {
                        int new_path = _dist[pos] + get_weight(graph, *it, nodex);
                        if (min > new_path) {
                            min = new_path;
                        }
                    }
                }
            }
        }
        int node_pos = locate(graph, nodex);
        _dist[node_pos] = min;

        VNode* last_but_one = nullptr;
        // 调整 _dist
        _s.insert(nodex);
        _v_s.erase(nodex);
        for (auto it = _s.begin(); it != _s.end(); it++) {
            for (ArcNode* cur = (*it)->firstarc; cur; cur = cur->nextarc) {
                if (_s.find(vec[cur->pos]) == _s.end()) {
                    int pos = locate(graph, *it);
                    if (_dist[pos] < INFINITY_MAX) {
                        int new_path = _dist[pos] + get_weight(graph, *it, vec[cur->pos]);
                        if (_dist[cur->pos] > new_path) {
                            _dist[cur->pos] = new_path;
                        }
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < _dist.size(); i++) {
        printf("_dist[%d]=%d\n", i, _dist[i]);
    }
}

int main()
{
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

        dijkstra(G, node5);

        destroy(G);
    }

    {
        Graph G;
        VNode* node0 = add_vertex(G, 0);
        VNode* node1 = add_vertex(G, 1);
        VNode* node2 = add_vertex(G, 2);
        VNode* node3 = add_vertex(G, 3);
        VNode* node4 = add_vertex(G, 4);
        VNode* node5 = add_vertex(G, 5);

        add_arc(G, node0, node1, 30);
        add_arc(G, node0, node2, 60);
        add_arc(G, node0, node4, 150);
        add_arc(G, node0, node5, 40);

        add_arc(G, node1, node2, 40);
        add_arc(G, node1, node3, 100);

        add_arc(G, node2, node3, 50);
        add_arc(G, node3, node4, 30);
        add_arc(G, node4, node5, 10);

        dijkstra(G, node0);

        destroy(G);
    }
    
    
    return 0;
}