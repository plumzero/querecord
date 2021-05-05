
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DataType;

#include "LinkList.h"

/**
 * 如果在单链表 A 中出现的元素在单链表 B 中也出现，则将 A 中的元素删除。
 * 即求两个集合的差集 A - B
 */

void DelElem(LinkList A, LinkList B)
{
    int i, pos;
    DataType e;
    ListNode * p;
    
    for (i = 1; i <= ListLength(B); i++) {
        p = Get(B, i);
        if (p) {
            pos = LocatePos(A, p->data);
            if (pos > 0) {
                DeleteList(A, pos, &e);
            }
        }
    }
}

/**
 * pre, p, r 是指向 A 链表的指针， q 是指向 B 链表的指针
 * p 和 q 是要比较的节点
 */
void DelElem2(LinkList A, LinkList B)
{
    ListNode * pre, * p, * r;
    ListNode * q;
    
    pre = A;
    // 开始时，p 和 q 均指向对应链表的第一个有效节点
    p = A->next;
    q = B->next;
    
    while (p != NULL) {
        q = B->next;
        while (q != NULL && q->data != p->data) {
            q = q->next;
        }
        if (q != NULL) {
            r = p;
            pre->next = p->next;
            p = r->next;    // p 指向下一个待比较的节点
            free(r);
        } else {
            pre = p;
            p = p->next;
        }
    }
    
}

int main()
{
    int i;
    DataType a[] = { 2, 3, 6, 7, 9, 14, 56, 45, 65, 67 };
    DataType b[] = { 3, 4, 7, 11, 34, 54, 45, 67 };
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
    
    DelElem2(A, B);
    printf("将在 A 中出现 B 的元素删除后(A-B)，现在A中的元素还有 %d 个:\n", ListLength(A));
    for (i = 1; i <= ListLength(A); i++) {
        p = Get(A, i);
        if (p)
            printf("%4d", p->data);
    }
    printf("\n");
    
    return 0;
}