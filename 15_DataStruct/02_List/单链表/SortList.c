
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DataType;

#include "LinkList.h"

/**
 * 将一个无序的单链表变成一个有序的单链表，要求按照从小到大排列并且不占用额外存储空间。
 * 
 * 头插法。
 */
 
void SortList(LinkList H)
{
    ListNode * p, * q;      // 原链表
    ListNode * pre, * pn;   // 新链表
    
    p = H->next;    // 第一个有效节点
    
    H->next = NULL; // 将头结点从原链表中断开
        
    // 在新链表中插入第一个有效节点作为比较节点
    pn = p;
    p = p->next;
    pn->next = H->next;
    H->next = pn;

    while (p != NULL) {
        pn = H->next;
        while (pn != NULL && p->data >= pn->data){  // 在新链表中找到比待插入节点大的节点或到达新链表末尾
            pre = pn;
            pn = pn->next;
        }
        
        q = p->next;
        p->next = pn;
        pre->next = p;
        p = q;
    }
}
 
int main()
{
    int i;
    DataType a[] = { 6, 79, 91, 14, 137, 415, 35, 67 };
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
    
    SortList(A);
    printf("排序后的链表:\n");
    for (i = 1; i <= ListLength(A); i++) {
        p = Get(A, i);
        if (p) {
            printf("%4d", p->data);
        }
    }
    printf("\n");
    
    return 0;
}