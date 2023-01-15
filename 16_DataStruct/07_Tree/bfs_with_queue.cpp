
// 通过队列进行 bfs

#include "btree.h"
#include <queue>

//     1
//    / \
//   2   3
//  /   / \
// 4   5   6
//      \
//       7

void bfs_with_queue(BinTreeNode* root)
{
    if (root == nullptr)
        return ;

    std::queue<BinTreeNode*> que;
    que.push(root);

    while (! que.empty()) {
        BinTreeNode* node = que.front();
        que.pop();
        printf("%d ", node->val);
        if (node->left != nullptr) que.push(node->left);
        if (node->right != nullptr) que.push(node->right);
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

    bfs_with_queue(node1);

    destroy_tree(&node1);

    return 0;
}