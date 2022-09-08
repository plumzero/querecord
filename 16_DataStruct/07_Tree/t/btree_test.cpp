
#include "btree.h"

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

    preorder_print(node1);
    printf("\n");
    preorder_print2(node1);

    inorder_print(node1);
    printf("\n");
    inorder_print2(node1);

    postorder_print(node1);
    printf("\n");
    postorder_print2(node1);

    return 0;
}