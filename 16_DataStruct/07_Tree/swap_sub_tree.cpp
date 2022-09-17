
// 交换左右子树

#include <stdio.h>

#include "btree.h"


void swap(BinTreeNode** root)
{
    if (*root != nullptr) {
        BinTreeNode* node = (*root)->left;
        (*root)->left = (*root)->right;
        (*root)->right = node;
        swap(&(*root)->left);
        swap(&(*root)->right);
    }
}

//      1
//    /  \
//   2    3
//  / \   /
// 4   5 6

// 转换后
//      1
//    /  \
//   3    2
//    \  / \
//     6 5  4

int main()
{
    BinTreeNode* node1 = create_node(1);
    BinTreeNode* node2 = create_node(2);
    BinTreeNode* node3 = create_node(3);
    BinTreeNode* node4 = create_node(4);
    BinTreeNode* node5 = create_node(5);
    BinTreeNode* node6 = create_node(6);

    connect_node(node1, node2, node3);
    connect_node(node2, node4, node5);
    connect_node(node3, node6, nullptr);

    swap(&node1);

    // 1 3 6 2 5 4
    preorder_print2(node1);
    // 3 6 1 5 2 4
    inorder_print2(node1);

    destroy_tree(&node1);

    return 0;
}