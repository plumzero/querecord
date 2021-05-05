
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int DataType;

#include "LinkList.h"

/**
 * 两个单链表 A B ，元素均由小到大排列。
 * 求 A 和 B 的交集 C。
 */

void InterSection(LinkList A, LinkList B, LinkList C)
{
    ListNode * p, * q, * r;
    ListNode * pc;
    
    pc = C;
    
    // 找到各链表的起始有效节点
    p = A->next;
    q = B->next;
    
    while (p != NULL && q != NULL) {
        if (p->data > q->data) {    // B 向后移
            q = q->next;
        } else if (p->data < q->data) {
            p = p->next;
        } else {
            r = (ListNode*)malloc(sizeof(ListNode));
            assert(r != NULL);
            r->data = p->data;
            r->next = pc->next;
            pc->next = r;
            pc = r;
            
            p = p->next;
            q = q->next;
        }
    }
}


int main()
{
    int i;
    DataType a[] = { 6, 7, 9, 14, 37, 45, 65, 67 };
    DataType b[] = { 3, 7, 11, 34, 45, 89 };
    LinkList A, B, C;
    ListNode * p;
    
    InitList(&A);
    InitList(&B);
    InitList(&C);
    
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

    InterSection(A, B, C);
    printf("单链表A和单链表B的交集C中的元素有 %d 个:\n", ListLength(C));
    for (i = 1; i <= ListLength(C); i++) {
        p = Get(C, i);
        if (p) {
            printf("%4d", p->data);
        }
    }
    printf("\n");
    
    return 0;
}