
// 07 重建二叉树

// 问题:
// 给出二叉树的前序序列和中序序列，重建此二叉树。
// 假设要构建的二叉树节点中无重复数字。

// 注意: 仅给出前序序列和后序序列，无法构建出二叉树，必须再给出一个中序序列

// 分析:
// 根椐前序遍历特点，可以知道前序序列中首个节点为根节点。再得到根节点在中序序列中的位置，以该节点左侧
// 构建左子树，以该节点右侧构建右子树
// 可以看出，这个构造过程类似前序遍历，即先构造根节点，再构建左子树，最后构建右子树。可以按照这个思路
// 写个框框

#include <stdio.h>
#include "btree.h"

// 前序: 1 2 4 7 3 5 6 8
// 后序: 4 7 2 1 5 3 8 6
BinTreeNode* _construct_tree(int preorder[], int pb, int pe, int inorder[], int ib, int ie)
{
    int x;
    for (x = ib; x <= ie; x++) {
        if (inorder[x] == preorder[pb])
            break;
    }

    BinTreeNode* root = new BinTreeNode();
    root->val = preorder[pb];
    int left_count = x - ib;
    int right_count = ie - x;

    if (left_count > 0) {
        root->left = _construct_tree(preorder, pb + 1, pb + left_count, inorder, ib, x - 1);
    }
    if (right_count > 0) {
        root->right = _construct_tree(preorder, pb + left_count + 1, pe, inorder, x + 1, ie);
    }

    return root;
}

BinTreeNode* construct_tree(int preorder[], int inorder[], int len)
{
    // assert(preorder != nullptr && inorder != nullptr && len > 0);

    return _construct_tree(preorder, 0, len - 1, inorder, 0, len - 1);
}

// 示例树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
int main()
{
    {
        const int len = 8;
        int preorder[len] = {1, 2, 4, 7, 3, 5, 6, 8};
        int inorder[len] = {4, 7, 2, 1, 5, 3, 8, 6};

        BinTreeNode* root = construct_tree(preorder, inorder, len);

        postorder_print2(root);

        destroy_tree(&root);
    }

    {
        const int len = 2;
        int preorder[len] = {1, 2};
        int inorder[len] = {2, 1};

        BinTreeNode* root = construct_tree(preorder, inorder, len);

        postorder_print2(root);

        destroy_tree(&root);   
    }

    {
        const int len = 1;
        int preorder[len] = {1};
        int inorder[len] = {1};

        BinTreeNode* root = construct_tree(preorder, inorder, len);

        postorder_print2(root);

        destroy_tree(&root);   
    }

    return 0;
}