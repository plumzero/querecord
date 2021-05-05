

/**
 * 约瑟夫问题。
 * 有 n 个人，编号为 1，2，...,n 。围成一个圆圈，按照顺时针方向从编号为 k 的人从 1 开始报数，报数为 m 的
 * 人出列，他的下一个人重新开始从 1 报数，数到 m 的人出列，这样重复下去，直到所有的人都出列。
 * 编写一个算法，要求输入 n, k, m ，按照出列的顺序输出编号。
 *
 * 解决约瑟夫问题分为三个步骤:
 *  1. 建立一个具有 n 个节点的不带头结点的循环单链表，编号从 1 到 n
 *  2. 找到第 k 个结点，即第一个开始报数的人
 *  3. 编号为 k 的人从 1 开始报数，并开始计数，报到 m 的人出列，即将该节点删除。继续从下一个节点开始报数，
 *     直到最后一个节点被删除。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DataType;
typedef struct Node {
    DataType data;
    struct Node * next;
} ListNode, * LinkList;

/** 创建循环单链表 */
LinkList CreateCyList(int n)
{
    ListNode * head = NULL;
    ListNode * p, * q;
    int i;
    
    for (i = 1; i <= n; i++) {
        p = (ListNode*)malloc(sizeof(ListNode));
        p->data = i;
        p->next = NULL;
        if (head == NULL) {
            head = p;
        } else {
            q->next = p;
        }
        q = p;
    }
    p->next = head;
    
    return head;
}

void Josephus(LinkList head, int n, int m, int k)
{
    ListNode * p, * q;
    int i;
    
    // 定位第 1 个节点
    p = head;
    i = 1;
    // 定位第 k 个节点
    while (i < k) {
        q = p;
        p = p->next;
        i++;
    }
    
    while (p->next != p) {
        for (i = 1; i < m; i++) {   // 数到 m 的人出列
            q = p;
            p = p->next;
        }
        q->next = p->next;
        printf("%4d", p->data);
        free(p);
        p = q->next;
    }
    printf("%4d\n", p->data);
    
}

int main()
{
    LinkList h;
    int n, k, m;
    printf("输入环中人的个数 n=");
    scanf("%d", &n);
    printf("输入开始报数的序号 k=");
    scanf("%d", &k);
    printf("报数为m的人出列 m=");
    scanf("%d", &m);
    
    h = CreateCyList(n);
    Josephus(h, n, m, k);
    
    return 0;
}