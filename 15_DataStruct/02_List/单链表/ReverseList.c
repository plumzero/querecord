
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DataType;

#include "LinkList.h"

/**
 * 顺序表的就地逆置
 * 即将
 *  (a1, a2, ..., an)
 * 转化为
 *  (an, ..., a2, a1)
 *
 * 1. 将头结点断开，将第一个有效节点取下，用头结点指针指向它。
 * 2. 将后续有效结点依次插入到头结点与第一个有效节点(不断改变)之间。
 */

void ReverseList(LinkList H)
{
    ListNode * p, * q;
    
    // 指向第一个有效节点
    p = H->next;
    H->next = NULL;
    
    while (p != NULL) {
        q = p->next;
        p->next = H->next;
        H->next = p;
        p = q;
    }
}

int main()
{
    int i;
    DataType a[] = { 6, 7, 9, 14, 37, 45, 65, 67 };
    LinkList A;
    ListNode * p;
    
    InitList(&A);
    
    for (i = 1; i <= sizeof(a)/sizeof(a[0]); i++) {
        if (InsertList(A, i, a[i - 1]) == 0) {
            printf("位置不合法\n");
            return -1;
        }
    }
    
    printf("单链表A中的元素有 %d 个:\n", ListLength(A));
    for (i = 1; i <= ListLength(A); i++) {
        p = Get(A, i);
        if (p) {
            printf("%4d", p->data);
        }
    }
    printf("\n");
    
    ReverseList(A);
    printf("倒置链表后:\n");
    for (i = 1; i <= ListLength(A); i++) {
        p = Get(A, i);
        if (p) {
            printf("%4d", p->data);
        }
    }
    printf("\n");
    
    return 0;
}