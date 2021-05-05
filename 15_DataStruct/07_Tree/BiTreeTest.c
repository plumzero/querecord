
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char DataType;
#define MAXSIZE 100

#include "LinkBiTree.h"

/**
 * 先序输入序列: ABD#G##EH##I##CF#J###
 */
 
/**
    根据输入二叉树的先序序列创建二叉树('#'表示结束):
    ABD#G##EH##I##CF#J###
    先序遍历:
     A B D G E H I C F J
    中序遍历:
     D G B H E I A F J C
    后序遍历:
     G D H I E B J F C A
 */

int main()
{
    BiTree T;
    
    InitBitTree(&T);
    printf("根据输入二叉树的先序序列创建二叉树('#'表示结束):\n");
    CreateBitTree(&T);
    
    /** 遍历 */
    printf("先序遍历:\n");
    PreOrderTraverse(T);
    printf("\n");
    
    printf("中序遍历:\n");
    InOrderTraverse(T);
    printf("\n");
    
    printf("后序遍历:\n");
    PostOrderTraverse(T);
    printf("\n");
    
    /** 计数 */
    printf("叶子结点个数=%d\n", LeafCount(T));
    printf("非叶子结点个数=%d\n", NotLeafCount(T));
    printf("深度=%d\n", BitTreeDepth(T));
    
    DestroyBitTree(&T);
    
    return 0;
}