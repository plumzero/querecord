
// 08 二叉树的下一个节点

// 问题: 给定一棵二叉树和其中的一个节点，找出中序遍历序列的下一个节点。

// 分析:
// 以中序遍历为基础，在找到给定节点时，设置一个已找到标记，在遍历下一个节点时若标记已设置，则返回该节点

#include <stdio.h>

#include "btree.h"

#include <stack>

BinTreeNode* get_next(BinTreeNode* root, BinTreeNode* cur)
{
    if (root != nullptr) {
        std::stack<BinTreeNode*> _stack;
        bool found = false;

        BinTreeNode* node = root;
        while (node || _stack.size() > 0) {
            while (node) {
                _stack.push(node);
                node = node->left;
            }
            if (_stack.size()) {
                node = _stack.top();
                _stack.pop();
                if (found) {
                    return node;
                }
                if (node == cur) {
                    found = true;
                }
                node = node->right;
            }
        }
    }

    return nullptr;
}

void print_next(BinTreeNode* root, BinTreeNode* cur)
{
    BinTreeNode* next = get_next(root, cur);
    printf("%d -> ", cur->val);
    if (next != nullptr) {
        printf("%d", next->val);
    }
    printf("\n");
}

//     1
//    / \
//   2   3
//  /   / \
// 4   5   6
//      \
//       7
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

    inorder_print2(node1);
    
    print_next(node1, node1);
    print_next(node1, node2);
    print_next(node1, node3);
    print_next(node1, node4);
    print_next(node1, node5);
    print_next(node1, node6);
    print_next(node1, node7);

    return 0;
}