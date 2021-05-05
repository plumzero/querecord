

typedef struct Node
{
    DataType    data;
    struct Node * lchild;
    struct Node * rchild;
} *BiTree, BitNode;

/** 二叉树的初始化 */
void InitBitTree(BiTree * T)
{
    *T = NULL;
}
/** 二叉树的销毁 */
void DestroyBitTree(BiTree * T)
{
    if (*T) {
        if ((*T)->lchild)
            DestroyBitTree(&((*T)->lchild));
        if ((*T)->lchild)
            DestroyBitTree(&((*T)->lchild));
        free(*T);
        *T = NULL;
    }
}
/** 创建二叉树，输入'#'时表示为空 */
void CreateBitTree(BiTree * T)
{
    DataType ch;
    scanf("%c", &ch);
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BitNode*)malloc(sizeof(BitNode)); // 创建结点
        (*T)->data = ch;
        CreateBitTree(&((*T)->lchild));         // 构造左子树
        CreateBitTree(&((*T)->rchild));         // 构造右子树
    }
}
/** 返回二叉树结点的指针操作(队列实现) */
BitNode* Point(BiTree T, DataType e)
{
    BitNode * Q[MAXSIZE];       // 存放二叉树结点的指针
    int front = 0, rear = 0;    // 初始化队列
    BitNode * p;
    
    if (T) {
        Q[rear] = T;
        rear++;
        
        while (front != rear) { // 队列非空
            p = Q[front];       // 出队
            front++;
            if (p->data == e) {
                return p;
            }
            if (p->lchild) {    // 左孩子结点入队
                Q[rear] = p->lchild;
                rear++;
            }
            if (p->rchild) {    // 右孩子结点入队
                Q[rear] = p->rchild;
                rear++;
            }
        }
    }
    
    return NULL;
}
/** 返回二叉树的结点的左孩子元素值 */
DataType LeftChild(BiTree T, DataType e)
{
    BiTree p;
    
    if (T) {
        p = Point(T, e);
        if (p && p->lchild) {
            return p->lchild->data;
        }
    }
    return '#';
}
/** 返回二叉树的结点的右孩子元素值 */
DataType RightChild(BiTree T, DataType e)
{
    BiTree p;
    
    if (T) {
        p = Point(T, e);
        if (p && p->rchild) {
            return p->rchild->data;
        }
    }
    return '#';
}
/** 左子树删除 */
int DeleteLeftChild(BiTree p)
{
    if (p) {
        DestroyBitTree(&(p->lchild));
        return 1;
    }
    return 0;
}
/** 右子树删除 */
int DeleteRightChild(BiTree p)
{
    if (p) {
        DestroyBitTree(&(p->rchild));
        return 1;
    }
    return 0;
}
/** 先序遍历 */
void PreOrderTraverse(BiTree T)
{
    if (T) {
        printf("%2c", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
/** 中序遍历 */
void InOrderTraverse(BiTree T)
{
    if (T) {
        InOrderTraverse(T->lchild);
        printf("%2c", T->data);
        InOrderTraverse(T->rchild);
    }
}
/** 后序遍历 */
void PostOrderTraverse(BiTree T)
{
    if (T) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%02c", T->data);
    }
}
/** 统计叶子结点 */
int LeafCount(BiTree T)
{
    if (! T) {
        return 0;
    } else if (! T->lchild && ! T->rchild) {
        return 1;
    } else {
        return LeafCount(T->lchild) + LeafCount(T->rchild);
    }
}
/** 统计非叶子结点个数 */
int NotLeafCount(BiTree T)
{
    if (! T) {
        return 0;
    } else if (! T->lchild && ! T->rchild) {
        return 0;
    } else {
        return NotLeafCount(T->lchild) + NotLeafCount(T->rchild) + 1;
    }
}
/** 计算二叉树的深度 */
int BitTreeDepth(BiTree T)
{
    if (! T) {
        return 0;
    } else if (! T->lchild && ! T->rchild) {
        return 1;
    } else {
        return BitTreeDepth(T->lchild) > BitTreeDepth(T->rchild) ?
               BitTreeDepth(T->lchild) + 1 :
               BitTreeDepth(T->rchild) + 1;
    }
}