
// 无向图中，求距离顶点 v 的最短路径长度为 k 的所有顶点
// 注: 最短路径长度以边数为单位计算，要求尽可能地节省时间

// 广度优先遍历的应用

#include "mgraph.h"
#include <queue>

void shortest_path_k(MGraph& graph, VNode* v, int k)
{
    std::vector<VNode*> vec = graph.vertex;
    auto & arc = graph.arc;
    std::queue<VNode*> _queue;
    std::vector<int> _visited(graph.vertex.size(), 0);
    int cur, next;
    int level = 0;

    _queue.push(v);
    cur = 1;
    next = 0;
    while (_queue.size() > 0) {
        VNode* node = _queue.front();
        _queue.pop();
        cur--;
        int i = locate(graph, node);
        if (_visited[i] == 0) {
            _visited[i] = 1;
            if (level < k) {
                for (int j = 0; j < vec.size(); j++) {
                    if (arc[i][j] == 1 && _visited[j] == 0) {
                        _queue.push(vec[j]);
                        next++;
                    }
                }
            }
        }
        if (cur == 0) {
            cur = next;
            next = 0;
            level++;
            if (level == k) {
                while (_queue.size() > 0) {
                    printf("%d ", _queue.front()->val);
                    _queue.pop();
                }
                printf("\n");
            }
        }
    }
}

int main()
{
    MGraph G;

    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);
    VNode* node6 = add_vertex(G, 6);
    VNode* node7 = add_vertex(G, 7);
    VNode* node8 = add_vertex(G, 8);

    init_matrix(G);

    add_arc(G, node1, node2);
    add_arc(G, node1, node3);
    add_arc(G, node1, node4);
    add_arc(G, node2, node5);
    add_arc(G, node2, node6);
    add_arc(G, node3, node8);
    add_arc(G, node4, node7);
    add_arc(G, node5, node8);
    add_arc(G, node7, node8);

    shortest_path_k(G, node1, 1);   // 传入 0 或 3 时有 bug, 有点晕，后续解决

    destroy(G);

    return 0;
}