
### 树的相关概念
- 树的结点: 包含一个数据元素及若干指向子树分支的信息
- 结点的度: 一个结点拥有子树的个数，称为结点的度
- 叶子结点: 度为 0 的结点
- 分支结点: 度不为 0 的结点
- 孩子结点\双亲结点\子孙结点\祖先结点\兄弟结点: ...
- 树的度: 树中所有结点的度的最大值
- 树的层次: 根结点是第一层次，其他结点相对于根结点有各自的层次
- 树的深度: 树中所有结点的层次最大值

### 树的抽象数据模型
- 树的数据对象集合为树的各个结点的集合。
- 除根结点外，**一个数据元素可能有 m(m>=0) 个后继元素，但只有一个前驱元素**。

### 二叉树
- 满二叉树，完全二叉树
- 性质
    + 二叉树中，第m(m>=1)层上至多有 2^(m-1) 个结点。
    + 深度为k(k>=1)的二叉树至多有 2^k - 1 个结点。
    + 任何一棵二叉树，如果叶子结点总数为 n0, 度为 2 的结点总数为 n2, 则有 n0 = n2 + 1 。
    + 如果完全二叉树有 n 个结点，则深度为 floor(log2n) + 1 。

### 二叉树的存储实现
- 顺序存储
    + 数组实现，适合完全二叉树
- 链式存储
    + 二叉链表存储
    + 三叉链表存储: 比二叉链表存储多了一个双亲结点指针域

### 二叉树的遍历
- 二叉树的遍历过程其实是将二叉树的非线性序列转换成一个线性序列的过程。
- 先序遍历
- 中序遍历
- 后序遍历

### 二叉树的计数
- 统计二叉树的叶子结点个数
    + 当二叉树为空时，叶子结点个数为 0
    + 当二叉树只有一个根结点时，根结点就是叶子结点，叶子结点个数为 1
    + 其他情况下，计算左子树与右子树中叶子结点的和
- 统计二叉树的非叶子结点个数
    + 当二叉树为空时，非叶子结点个数为 0
    + 当二叉树只有根结点时，根结点为叶子结点，非叶子结点个数为 0
    + 其他情况下，计算左子树与右子树中非叶子结点的个数再加 1(根结点)
- 计算二叉树的深度
    + 当二叉树为空时，其深度为 0
    + 当二叉树只有根结点时，二叉树的深度为 1
    + 其他情况下，求二叉树的**左、右子树的最大值**再加 1(根结点)

### 二叉树的线索化

- 定义
	+ 二叉链表存储结构只能打到结点的左右孩子结点，无法找到一个结点的直接前驱结点和后继结点信息。
	+ 二叉链表存储结构中，具有 n 个结点的二叉链表有 n+1 个空指针域。可以利用这些空指针域存放结点的直接前驱与直接后继信息。规定如下: 
		+ 如果结点存在左子树，则指针域 lchild 指示其左孩子结点，否则，指针域 lchild 指示其直接前驱结点
		+ 如果结点存在右子树，则指针域 rchild 指示其右孩子结点，否则，指针域 rchild 指示其直接后继结点
	+ 为了区分指针域指向的是左孩子结点还是直接前驱结点，及是右孩子结点还是直接后继结点，增加两个标志域 ltag 和 rtag 。其中:
		+ 当 ltag=0 时，lchild 指示结点的左孩子；当 ltag=1 时，lchild 指示结点的直接前驱结点
		+ 当 rtag=0 时，rchild 指示结点的右孩子；当 rtag=1 时，lchild 指示结点的直接后继结点
	+ 由这种存储结构构成的二叉链表称为二叉树的线索二叉树。
- 分类
	+ 二叉树按照某种遍历方式使二叉树变为线索二叉树的过程称为二叉树的线索化。
	+ 先序线索化
	+ 中序线索化
	+ 后序线索化
- 方法
	+ 二叉树的线索化就是利用二叉树中结点的空指针域表示结点的前驱或后继信息。过程为:
		+ 对二叉树按某种方式进程遍历
		+ 遍历过程中将结点的空指针域改为某直接前驱或直接后继结点信息

### 速记

```c
    struct BinTreeNode {
        int val;
        BinTreeNode* left;
        BinTreeNode* right;
    };
```

概念:
- 根节点/叶节点/父节点/子节点
- 二叉树
- 遍历操作: 前序，中序，后序
- 广度优化遍历
- 完全二叉树/不完全二叉树
- 二叉搜索树
- 堆/最大堆/最小堆
- 红黑树

记忆:
- 根节点没有子节点，叶节点没有父节点。
- 层序遍历就是广度优先遍历。
- `前序 + 中序`、`中序 + 后序` 的组合可以构建一棵二叉树，但 `前序 + 后序` 的组合无法构建一棵二叉树。