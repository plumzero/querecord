
// 通过双数组进行 bfs

#include "btree.h"
#include <vector>

//     1
//    / \
//   2   3
//  /   / \
// 4   5   6
//      \
//       7

void bfs_with_two_array(BinTreeNode* root)
{
    if (root == nullptr)
        return ;

    std::vector<BinTreeNode*> vec[2];
    int cur = 0;
    int nxt = 1;
    vec[cur].push_back(root);

    while (! vec[cur].empty()) {
        for (auto node: vec[cur]) {
            printf("%d ", node->val);
            if (node->left != nullptr) vec[nxt].push_back(node->left);
            if (node->right != nullptr) vec[nxt].push_back(node->right);
        }
        vec[cur].clear();
        cur = 1 - cur;
        nxt = 1 - nxt;
    }
    printf("\n");
}

int main()
{
    BinTreeNode* node1 = create_node(1);
    BinTreeNode* node2 = create_node(2);
    BinTreeNode* node3 = create_node(3);
    BinTreeNode* node4 = create_node(4);
    BinTreeNode* node5 = create_node(5);
    BinTreeNode* node6 = create_node(6);
    BinTreeNode* node7 = create_node(7);

    connect_node(node1, node2, node3);
    connect_node(node2, node4, nullptr);
    connect_node(node3, node5, node6);
    connect_node(node5, nullptr, node7);

    bfs_with_two_array(node1);

    destroy_tree(&node1);

    return 0;
}