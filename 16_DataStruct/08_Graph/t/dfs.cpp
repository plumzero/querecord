
// 图的深度优先遍历

#include "graph.h"

#include <stack>
#include <vector>

// 从右侧的邻接点向左
void dfs1(Graph& graph)
{
    std::stack<VNode*> _stack;
    std::vector<int> _visited(graph.vertex.size());
    for (size_t i = 0; i < _visited.size(); i++) {
        _visited[i] = 0;
    }

    std::vector<VNode*> vec = graph.vertex;
    _stack.push(vec[0]);

    while (_stack.size() > 0) {
        VNode* node = _stack.top();
        _stack.pop();
        
        int pos = locate(graph, node);
        if (_visited[pos] == 0) {
            _visited[pos] = 1;
            printf("%d ", node->val);
            ArcNode* cur = node->firstarc;
            while (cur) {
                _stack.push(vec[cur->pos]);
                cur = cur->nextarc;
            }
        }
    }
    printf("\n");
}

// 从左侧的邻接点向右
void dfs2(Graph& graph)
{
    std::stack<VNode*> _stack;
    std::vector<int> _visited(graph.vertex.size());
    for (size_t i = 0; i < _visited.size(); i++) {
        _visited[i] = 0;
    }

    std::vector<VNode*> vec = graph.vertex;
    _stack.push(vec[0]);
    _visited[0] = 1;
    printf("%d ", vec[0]->val);

    while (_stack.size() > 0) {
        VNode* node = _stack.top();
        ArcNode* cur = node->firstarc;
        while (cur != nullptr && _visited[cur->pos] == 1) {
            cur = cur->nextarc;
        }
        if (cur != nullptr) {
            _stack.push(vec[cur->pos]);
            _visited[cur->pos] = 1;
            printf("%d ", vec[cur->pos]->val);
        } else {
            _stack.pop();
        }
    }
    printf("\n");
}

void _dfs3(Graph& graph, std::vector<int>& visited, int pos);
void dfs3(Graph& graph)     // 不如堆栈清晰
{
    std::vector<int> _visited(graph.vertex.size());
    for (size_t i = 0; i < _visited.size(); i++) {
        _visited[i] = 0;
    }

    std::vector<VNode*> vec = graph.vertex;
    for (size_t i = 0; i < vec.size(); i++) {
        if (_visited[i] == 0)
            _dfs3(graph, _visited, i);
    }
    printf("\n");
}

void _dfs3(Graph& graph, std::vector<int>& visited, int pos)
{
    visited[pos] = 1;
    printf("%d ", graph.vertex[pos]->val);
    
    VNode* node = graph.vertex[pos];
    ArcNode* cur = node->firstarc;
    while (cur != nullptr && visited[cur->pos] == 1) {
        cur = cur->nextarc;
    }
    if (cur) {
        _dfs3(graph, visited, cur->pos);
    }
}

//         1
//     /    \   \
//    2      3   4
//    \     /   / \
//     5 — 6   7 — 8
//             \
//              9

int main()
{
    Graph G;
    VNode* node1 = add_vertex(G, 1);
    VNode* node2 = add_vertex(G, 2);
    VNode* node3 = add_vertex(G, 3);
    VNode* node4 = add_vertex(G, 4);
    VNode* node5 = add_vertex(G, 5);
    VNode* node6 = add_vertex(G, 6);
    VNode* node7 = add_vertex(G, 7);
    VNode* node8 = add_vertex(G, 8);
    VNode* node9 = add_vertex(G, 9);

    add_arc(G, node1, node2);
    add_arc(G, node1, node3);
    add_arc(G, node1, node4);
    add_arc(G, node2, node1);
    add_arc(G, node2, node5);
    add_arc(G, node3, node1);
    add_arc(G, node3, node6);
    add_arc(G, node4, node1);
    add_arc(G, node4, node7);
    add_arc(G, node4, node8);
    add_arc(G, node5, node2);
    add_arc(G, node5, node6);
    add_arc(G, node6, node3);
    add_arc(G, node6, node5);
    add_arc(G, node7, node4);
    add_arc(G, node7, node8);
    add_arc(G, node7, node9);
    add_arc(G, node8, node4);
    add_arc(G, node8, node7);
    add_arc(G, node9, node7);

    display(G);

    dfs1(G);
    dfs2(G);
    dfs3(G);

    destroy(G);

    return 0;
}