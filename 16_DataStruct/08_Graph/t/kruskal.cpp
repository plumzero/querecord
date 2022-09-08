
#include "wgraph.h"

#include <vector>
#include <map>
#include <algorithm>

// 关于如何统计邻接表的边数?
// 如果依次遍历顶点数组中的每个元素，之后由每个顶点元素遍历对应的邻接点，肯定会出现冗余遍历的情况。
// 可以从比该顶点元素在顶点数组中的索引大的点开始遍历

// 关于如何进行集合的合并?
// 假设一共有 6 个顶点，开始时为每个顶点定义一个集合，那么一共需要 6 个集合，这种定义方法有些冗余
// 这样想，图中的顶点是存储在数组中的，通过数组的索引就可以找到对应的定点。不妨也定义一个同样长度
// 的数组，这个数组中索引对应的值就作为集合的名称。为了方便，数组存储各自的索引。如下:
//      索引  0 1 2 3 4 5
//        值  0 1 2 3 4 5
// 假设第一次索引 1 和 3 对应的边最小，那么将这两个顶点合并到一个集合中，比如集合 1，就是这样
//      索引  0 1 2 3 4 5
//        值  0 1 2 1 4 5
// 可以看到通过不断的合并，这个数组中存储的值最终只有一个，就达到了集合合并的目的。
void kruskal(Graph& graph)
{
    std::multimap<int, std::pair<VNode*, VNode*>> _map;  // 键为权重，利用其弱排序特性

    std::vector<VNode*> vec = graph.vertex;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        VNode* node = *it;
        int pos = std::distance(vec.begin(), it);
        for (ArcNode* cur = node->firstarc; cur; cur = cur->nextarc) {
            if (cur->pos > pos) {
                int weight = get_weight(graph, node, vec[cur->pos]);
                _map.insert(std::make_pair(weight, std::pair<VNode*,VNode*>(node,vec[cur->pos])));
            }
        }
    }

    std::vector<int> sets;
    for (size_t i = 0; i < vec.size(); i++) {
        sets.push_back(i);
    }

    while (_map.size() > 0) {
        auto it = _map.begin();
        VNode* node1 = it->second.first;
        VNode* node2 = it->second.second;
        int pos1 = locate(graph, node1);
        int pos2 = locate(graph, node2);
        if (sets[pos1] != sets[pos2]) {     // 若分属于不同的集合
            printf("%d-%d(%d)\n", node1->val, node2->val, get_weight(graph, node1, node2));
            // 将原来在 pos2 对应值中的集合元素都合并到 pos1 对应值的集合中
            int old_set = sets[pos2];
            std::replace_if(sets.begin(), sets.end(), [old_set](int i){ return i == old_set; }, sets[pos1]);
        }
        _map.erase(it);
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

    kruskal(G);

    destroy(G);

    return 0;
}