
// 返回最底层最左边的节点

#include "btree.h"
#include <queue>

//     1
//    / \
//   2   3
//  /   / \
// 4   5   6
//    / \
//   7   8

BinTreeNode* bottomest_leftest(BinTreeNode* root)
{
    if (root == nullptr)
        return nullptr;

    std::queue<BinTreeNode*> que;
    que.push(root);
    BinTreeNode* blnode = nullptr;

    while (! que.empty()) {
        BinTreeNode* node = que.front();
        que.pop();
        blnode = node;
        if (node->right != nullptr) que.push(node->right);
        if (node->left != nullptr) que.push(node->left);
    }

    return blnode;
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
    BinTreeNode* node8 = create_node(8);

    connect_node(node1, node2, node3);
    connect_node(node2, node4, nullptr);
    connect_node(node3, node5, node6);
    connect_node(node5, node7, node8);

    BinTreeNode* node = bottomest_leftest(node1);
    printf("val=%d\n", node->val);

    destroy_tree(&node1);

    return 0;
}