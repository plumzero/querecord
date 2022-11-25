
// 记录树中某个节点的开始访问时刻与结束访问时刻

// 一棵有根树 <=> 一组嵌套线段

#include <stdio.h>
#include "tree.h"

int _g = 0;

void pre_post_visit(TreeNode* root)
{
    root->start = _g++;
    for (auto& ele: root->children) {
        pre_post_visit(ele);
    }
    root->end = _g++;
}

//     1
//    / \  \
//   2   3  4
//      / \
//     5   6
//    / \
//   7   8
int main()
{
    TreeNode* node1 = create_node(1);
    TreeNode* node2 = create_node(2);
    TreeNode* node3 = create_node(3);
    TreeNode* node4 = create_node(4);
    TreeNode* node5 = create_node(5);
    TreeNode* node6 = create_node(6);
    TreeNode* node7 = create_node(7);
    TreeNode* node8 = create_node(8);

    connect_node(node1, node2);
    connect_node(node1, node3);
    connect_node(node1, node4);
    connect_node(node3, node5);
    connect_node(node3, node6);
    connect_node(node5, node7);
    connect_node(node5, node8);

    pre_post_visit(node1);

    level_print(node1);

    destroy_tree(&node1);

    return 0;
}