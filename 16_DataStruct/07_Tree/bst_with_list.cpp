
#include <stdio.h>

#include "bin_tree_node.h"

// 根据输入节点创建一棵二叉查找树
void add(BinTreeNode** btree, int val)
{
    BinTreeNode* node = new BinTreeNode();
    node->val = val;
    node->left = nullptr;
    node->right = nullptr;

    if (*btree == nullptr) {
        *btree = node;
    } else {
        BinTreeNode* cur = *btree;
        BinTreeNode* parent = nullptr;
        while (cur != nullptr) {
            parent = cur;
            if (cur->val > val)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (parent->val > val)
            parent->left = node;
        else
            parent->right = node;
    }
}

// 在查找树中查找元素
BinTreeNode* find(BinTreeNode* btree, int val)
{
    BinTreeNode* node = btree;
    while (node != nullptr) {
        if (node->val == val)
            return node;
        else if (node->val > val)
            node = node->left;
        else
            node = node->right;
    }

    return node;
}

// 查找树中删除元素
// 一共分成三种情况:
//  1. 删除节点为叶子节点，只要将其相连的父节点指针指向 null 即可
//  2. 删除的节点只有一棵子树，将该节点的父节点指针指向该节点子树的根节点，之后删除该节点
//  3. 删除的节点有两棵子树，可以有两种方法。对查找树的中序遍历是有序的，可以使用该节点的前一个节点替换掉该节点，或者
//      使用该节点的后一个节点替换掉该节点，之后删除该节点

// 通过分析可以看出，应该定义两个辅助指针，一个指向当前节点，一个指向当前节点的父节点
void remove(BinTreeNode** btree, int val)
{
    BinTreeNode* parent = nullptr;
    BinTreeNode* cur = *btree;
    while (cur != nullptr || cur->val != val) {
        if (cur->val == val) {
            if (cur->left == nullptr && cur->right == nullptr) {
                if (parent) {
                    if (parent->left == cur)
                        parent->left = nullptr;
                    else
                        parent->right = nullptr;
                } else {
                    // 根节点情况
                    *btree = nullptr;
                }
            } else if (cur->left == nullptr || cur->right == nullptr) { // 情况 2
                if (parent) {
                    if (parent->left == cur)
                        parent->left = (cur->left != nullptr) ? cur->left : cur->right;
                    else
                        parent->right = (cur->left != nullptr) ? cur->left : cur->right;
                } else {
                    // 根节点情况(这只是其中一种处理方法)
                    *btree = (cur->left != nullptr) ? cur->left : cur->right;
                }
            } else {
                BinTreeNode* prev = cur->left;
                BinTreeNode* prev_parent = cur;
                while (prev->right) {
                    prev_parent = prev;
                    prev = prev->right;
                }
                if (prev->left != nullptr) {
                    prev_parent->right = prev->left;
                }
                if (prev_parent->left == prev)
                    prev_parent->left = prev->left;
                else
                    prev_parent->right = prev->left;
                prev->left = cur->left;
                prev->right = cur->right;
                if (parent) {
                    if (parent->left == cur)
                        parent->left = prev;
                    else
                        parent->right = prev;
                } else {
                    *btree = prev;
                }
            }
            delete cur;
            cur = nullptr;
            return ;
        } else if (cur->val > val) {
            parent = cur;
            cur = cur->left;
        } else {
            parent = cur;
            cur = cur->right;
        }
    }
}
/*
		6
	   / \
	  3   7
	 / \   \
	2   5   8
	   /     \
	  4       9
*/
int main()
{
    int a[] = { 6, 3, 5, 4, 7, 8, 9, 2 };
    int len = sizeof(a) / sizeof(int);

    BinTreeNode* root = nullptr;
    for (int i = 0; i < len; i++) {
        add(&root, a[i]);
    }

    preorder_print(root);
    printf("\n");

    BinTreeNode* node;

    node = find(root, 8);
    if (node != nullptr) printf("yes! %d\n", node->val); else printf("no!\n");

    node = find(root, 1);
    if (node != nullptr) printf("yes! %d\n", node->val); else printf("no!\n");

    inorder_print(root);
    printf("\n");

    remove(&root, 6);
    inorder_print(root);
    printf("\n");

    remove(&root, 4);
    inorder_print(root);
    printf("\n");

    remove(&root, 3);
    inorder_print(root);
    printf("\n");

    destroy_tree(&root);

    return 0;
}