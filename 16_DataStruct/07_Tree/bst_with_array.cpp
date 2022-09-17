
// 使用一维数组来表示二叉树时，可将二叉树想象成一棵满二叉树，而且第 k 层具有 2^(k-1) 个节点，按序存放在一维数组中

// 为了计算方便，二叉树节点的存储最好从索引 1 开始，这样:
//  左子树索引值是父节点索引值乘 2
//  右子树索引值是父节点索引值乘 2 加 1


#include <stdio.h>

// 根据输入节点创建一棵二叉查找树
void create_bst(int* btree, int a[], int length)
{
    for (int i = 0; i < length; i++) {
        int j = 1;
        while (btree[j] != 0) {   // 与树的根节点比较。若数组内的值大于树根，则往右子树比较；否则往左子树比较
            if (a[i] > btree[j])
                j = j * 2 + 1;
            else
                j = j * 2;
        }
        btree[j] = a[i];
    }
}

int main()
{
    int a[] = { 6, 3, 5, 4, 7, 8, 9, 2 };
    int len = sizeof(a) / sizeof(int);
    int* btree = new int[16 + 1];

    create_bst(btree, a, len);

    for (int i = 1; i <= 15; i++) {
        printf("%d ", btree[i]);
    }
    printf("\n");

    delete btree;

    return 0;
}