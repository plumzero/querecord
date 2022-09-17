
// 已知中序序列为 4 2 7 5 1 3 6, 后序序列为 4 7 5 2 6 3 1，给出其对应的二叉树

#include <stdio.h>

#include "btree.h"

// a1 是中序序列，a2 是后序序列
BinTreeNode* construct_tree(int a1[], int is, int ie, int a2[], int ps, int pe)
{
    int val = a2[pe];
    BinTreeNode* root = new BinTreeNode();
    root->val = val;
    root->left = nullptr;
    root->right = nullptr;

    if (is == ie && ps == pe && a1[is] == a2[ps]) {
        return root;
    }

    int cur = is;
    while (cur <= ie && a1[cur] != a2[pe])
        cur++;

    int left_len = cur - is;
    if (left_len > 0) {
        root->left = construct_tree(a1, is, is + left_len - 1, a2, ps, ps + left_len - 1);
    }
    if (pe - ps > left_len) {
        root->right = construct_tree(a1, cur + 1, ie, a2, ps + left_len, pe - 1);
    }

    return root;
}

//     1
//    / \
//   2   3
//  / \   \
// 4   5   6
//    /
//   7

int main()
{
    int a1[] = { 4, 2, 7, 5, 1, 3, 6 };
    int a2[] = { 4, 7, 5, 2, 6, 3, 1 };
    int len = sizeof(a1) / sizeof(int);

    BinTreeNode* root = construct_tree(a1, 0, len - 1, a2, 0, len - 1);

    preorder_print2(root);
    tree_print(root);

    destroy_tree(&root);

    return 0;
}