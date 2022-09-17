
// 从根节点到某个节点之间的路径

#include <stdio.h>

#include "btree.h"

#include <vector>

// 注意观察采用不同的遍历方式时栈中的内容
void find_path(BinTreeNode* root, BinTreeNode* goal)
{
    if (root != nullptr) {
        std::vector<BinTreeNode*> _stack;

        BinTreeNode* node = root;
        BinTreeNode* rnode = nullptr;
        while (node || _stack.size() > 0) {
            while (node) {
                _stack.push_back(node);
                node = node->left;
            }
            if (_stack.size() > 0) {
                node = _stack.back();
                if (node->right == nullptr || node->right == rnode) {
                    if (node == goal) {
                        for (size_t i = 0; i < _stack.size(); i++) {
                            printf("%d ", _stack[i]->val);
                        }
                        _stack.clear();
                        node = nullptr;
                    } else {
                        rnode = node;
                        node = nullptr;
                        _stack.pop_back();
                    }
                } else {
                    node = node->right;
                }
            }
        }
        printf("\n");
    }
}

//      1
//    /  \
//   2    3
//  / \    \
// 4   5    6

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
    connect_node(node3, nullptr, node6);

    find_path(node1, node5);

    destroy_tree(&node1);

    return 0;
}