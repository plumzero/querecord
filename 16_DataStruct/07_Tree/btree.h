
#include <stdio.h>

#include <stack>

typedef struct BinTreeNode {
    int val;
    BinTreeNode* left;
    BinTreeNode* right;
} BinTreeNode;

BinTreeNode* create_node(int val)
{
    BinTreeNode* node = new BinTreeNode();
    node->val = val;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

void connect_node(BinTreeNode* parent, BinTreeNode* left, BinTreeNode* right)
{
    if (parent != nullptr) {
        parent->left = left;
        parent->right = right;
    }
}

void preorder_print(BinTreeNode* root)
{
    if (root != nullptr) {
        printf("%d ", root->val);
        preorder_print(root->left);
        preorder_print(root->right);
    }
}

void preorder_print2(BinTreeNode* root)
{
    if (root != nullptr) {
        std::stack<BinTreeNode*> _stack;

        BinTreeNode* node = root;
        while (node || _stack.size() > 0) {
            while (node) {
                printf("%d ", node->val);
                _stack.push(node);
                node = node->left;
            }
            if (_stack.size() > 0) {
                node = _stack.top();
                _stack.pop();
                node = node->right;
            }
        }
        printf("\n");
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

void inorder_print2(BinTreeNode* root)
{
    if (root != nullptr) {
        std::stack<BinTreeNode*> _stack;
        
        BinTreeNode* node = root;
        while (node || _stack.size() > 0) {
            while (node) {
                _stack.push(node);
                node = node->left;
            }
            if (_stack.size() > 0) {
                node = _stack.top();
                _stack.pop();
                printf("%d ", node->val);
                node = node->right;
            }
        }
        printf("\n");
    }
}

void postorder_print(BinTreeNode* root)
{
    if (root != nullptr) {
        postorder_print(root->left);
        postorder_print(root->right);
        printf("%d ", root->val);
    }
}

void postorder_print2(BinTreeNode* root)
{
    if (root != nullptr) {
        std::stack<BinTreeNode*> _stack;
        
        BinTreeNode* node = root;
        BinTreeNode* rnode = nullptr;       // rnode 指向最近一次访问过的某子树的右节点(当然，实际程序中也会指向左边节点)
        while (node || _stack.size() > 0) {
            while (node) {
                _stack.push(node);
                node = node->left;
            }
            if (_stack.size() > 0) {
                node = _stack.top();
                if (node->right == nullptr || node->right == rnode) { // 如果 node 没有右孩子节点，或者右孩子节点已经访问过
                    printf("%d ", node->val);
                    rnode = node;
                    node = nullptr;
                    _stack.pop();
                } else {
                    node = node->right;
                }
            }
        }
        printf("\n");
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

#include <queue>

void level_print(BinTreeNode* root)
{
    if (root != nullptr) {
        std::queue<BinTreeNode*> _queue;
        _queue.push(root);
        
        while (_queue.size() > 0) {
            BinTreeNode* node = _queue.front();
            _queue.pop();
            printf("%d ", node->val);
            if (node->left) {
                _queue.push(node->left);
            }
            if (node->right) {
                _queue.push(node->right);
            }
        }
        printf("\n");
    }
}

void tree_print(BinTreeNode* root)
{
    if (root != nullptr) {
        std::queue<BinTreeNode*> _queue;
        _queue.push(root);
        int cur = 1;
        int next = 0;
        
        while (_queue.size() > 0) {
            BinTreeNode* node = _queue.front();
            _queue.pop();
            cur--;
            printf("%d ", node->val);
            if (node->left) {
                _queue.push(node->left);
                next++; 
            }
            if (node->right) {
                _queue.push(node->right);
                next++;
            }
            if (cur == 0) {
                printf("\n");
                cur = next;
                next = 0;
            }
        }
        printf("\n");
    }
}

// 深度
int tree_depth(BinTreeNode* root)
{
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;

    int left_depth = 0;
    int right_depth = 0;
    if (root->left)
        left_depth = 1 + tree_depth(root->left);
    if (root->right)
        right_depth = 1 + tree_depth(root->right);

    return std::max(left_depth, right_depth);
}