
#include <stdio.h>

#include "btree.h"

#include <queue>

// 完全二叉树中，若某节点无左子节点，则一定无右子节点
bool is_complete(BinTreeNode* root)
{
    if (root == nullptr)
        return true;

    std::queue<BinTreeNode*> _queue;
    
    int flag = 0;

    _queue.push(root);
    while (_queue.size() > 0) {
        BinTreeNode* node = _queue.front();
        _queue.pop();
        
        if (node != nullptr) {
            _queue.push(node->left);
            _queue.push(node->right);
        } else {
            while (_queue.size() > 0) {
                BinTreeNode* null_node = _queue.front();
                _queue.pop();
                if (null_node != nullptr) {
                    return false;
                }
            }
        }
    }

    return true;
}

//      1
//    /  \
//   2    3
//  / \   /
// 4   5 6

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
    // connect_node(node3, node6, nullptr);
    connect_node(node3, nullptr, node6);

    printf("%s\n", is_complete(node1) ? "yes" : "no");

    destroy_tree(&node1);

    return 0;
}