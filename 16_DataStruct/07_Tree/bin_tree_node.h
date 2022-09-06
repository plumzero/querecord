
#include <stdio.h>

typedef struct BinTreeNode {
    int val;
    BinTreeNode* left;
    BinTreeNode* right;
} BinTreeNode;

void preorder_print(BinTreeNode* root)
{
    if (root != nullptr) {
        printf("%d ", root->val);
        preorder_print(root->left);
        preorder_print(root->right);
    }
}

void inorder_print(BinTreeNode* root)
{
    if (root != nullptr) {
        inorder_print(root->left);
        printf("%d ", root->val);
        inorder_print(root->right);
    }
}

void destroy_tree(BinTreeNode** root)
{
    if (root != nullptr && *root != nullptr) {
        destroy_tree(&((*root)->left));
        destroy_tree(&((*root)->right));
        delete (*root);
        *root = nullptr;
    }
}