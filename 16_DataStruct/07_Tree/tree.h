
#include <vector>
#include <queue>
#include <stdio.h>

typedef struct TreeNode {
    int val;
    std::vector<TreeNode*> children;
    int start;
    int end;
} TrueNode;

// 非二叉树很难进行中序遍历

TreeNode* create_node(int val)
{
    TreeNode* node = new TreeNode();
    node->val = val;
    node->start = node->end = -1;
    node->children.clear();

    return node;
}

void connect_node(TreeNode* parent, TreeNode* child)
{
    if (parent != nullptr && child != nullptr) {
        parent->children.push_back(child);
    }
}

void preorder_print(TreeNode* root)
{
    if (root != nullptr) {
        printf("%d ", root->val);
        for (const auto& ele: root->children) {
            preorder_print(ele);
        }
    }
}

void postorder_print(TreeNode* root)
{
    if (root != nullptr) {
        for (const auto& ele: root->children) {
            postorder_print(ele);
        }
        printf("%d ", root->val);
    }
}

void level_print(TreeNode* root)
{
    if (root != nullptr) {
        std::queue<TreeNode*> _queue;
        _queue.push(root);
        
        while (_queue.size() > 0) {
            TreeNode* node = _queue.front();
            _queue.pop();
            printf("%d(%d|%d) ", node->val, node->start, node->end);
            for (const auto& ele: node->children) {
                _queue.push(ele);
            }
        }
        printf("\n");
    }
}

void destroy_tree(TreeNode** root)
{
    if (root != nullptr && *root != nullptr) {
        for (auto& ele: (*root)->children) {
            destroy_tree(&ele);
        }
        delete (*root);
        *root = nullptr;
    }
}