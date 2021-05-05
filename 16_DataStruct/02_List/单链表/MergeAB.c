
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 存在两个单链表 A 和 B, 其中的元素都是非递减排列。现在将单链表 B 归并到单链表 A ，得到的单链表
 * A 中的元素的值仍然按照非递减排列。
 * 要求不申请额外空间。
 */

typedef int DataType;

#include "LinkList.h"

/**
 * 将 B 中的元素依次与 A 中的元素进行比较，之后将 B 中元素插入到 A 中。
 */
void MergeList(LinkList A, LinkList B)
{
    ListNode * pre, * p;    // A 链表中的相关指针
    ListNode * q;           // B 链表中的相关指针
    
    pre = A;
    // p q 指向各自链表的第一个节点
    p = A->next;
    q = B->next;
    
    while (p != NULL && q != NULL) {
        if (p->data <= q->data) {   // q 不变，p 向后移一位
            pre = pre->next;
            p = p->next;
            
        } else {                    // 将 q 插入到 A 链表中，随后 q 后移一位
            pre->next = q;
            q = q->next;
            pre->next->next = p;
            pre = pre->next;
        }
    }
    if (q != NULL) {
        pre->next = q;
    }
}

int main()
{
    int i;
    DataType a[] = { 6, 7, 9, 14, 37, 45, 65, 67 };
    DataType b[] = { 3, 7, 11, 34, 45, 89 };
    LinkList A, B;
    ListNode * p;
    
    InitList(&A);
    InitList(&B);
    
    for (i = 1; i <= sizeof(a)/sizeof(a[0]); i++) {
        if (InsertList(A, i, a[i - 1]) == 0) {
            printf("位置不合法\n");
            return -1;
        }
    }
    for (i = 1; i <= sizeof(b)/sizeof(b[0]); i++) {
        if (InsertList(B, i, b[i - 1]) == 0) {
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
    printf("单链表B中的元素有 %d 个:\n", ListLength(B));
    for (i = 1; i <= ListLength(B); i++) {
        p = Get(B, i);
        if (p) {
            printf("%4d", p->data);
        }
    }
    printf("\n");
    
    MergeList(A, B);
    printf("将单链表A和B的元素合并后，A中的元素有%d个:\n", ListLength(A));
    for (i = 1; i <= ListLength(A); i++) {
        p = Get(A, i);
        if (p) {
            printf("%4d", p->data);
        }
    }
    printf("\n");
    
    return 0;
}