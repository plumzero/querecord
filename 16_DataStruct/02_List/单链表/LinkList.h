
#pragma once

/// 单链表的结构定义
typedef struct Node
{
    DataType data;
    struct Node * next;
} ListNode, * LinkList;

/// 单链表的基本运算
/** 
 * 单链表的初始化操作。
 * 将单链表初始化为空。动态生成一个头结点，并将头结点的指针域置为空。
 */
void InitList(LinkList * head)
{
    if ((*head = (ListNode*)malloc(sizeof(ListNode))) == NULL) {
        exit(-1);
    }
    (*head)->next = NULL;
}
/**
 * 判断单链表是否为空。
 * 判断单链表是否为空，就是看单链表的头结点的指针域是否为空。
 */
int ListEmpty(LinkList head)
{
    if (head->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}
/**
 * 按序号查找操作。
 * 按序号查找就是查找单链表中的第 i 个结点，如果找到，返回该结点的指针；否则，返回 NULL，表示失败。
 * 因为引入了头结点，这里有效节点序号从 1 开始。
 */
ListNode * Get(LinkList head, int i)
{
    ListNode * p;
    int j;
    
    if (ListEmpty(head))
        return NULL;
    if (i < 1)
        return NULL;
    
    // 定位要查找链表的第一个节点
    p = head->next;                 // 指向第一个有效节点
    j = 1;                          // 第一个有效节点的序号
    
    while (p != NULL && j < i) {    // 当前节点不为空，且还没有到达要找的序号节点，则寻找下一个节点
        p = p->next;
        j++;                        
    }
    if (j == i)
        return p;
    else
        return NULL;
}
/**
 * 按内容查找操作。
 * 查找线性表中元素值为 e 的元素，查找成功将对应元素的节点指针返回，否则返回 NULL，表示失败。
 */
ListNode * LocateElem(LinkList head, DataType e)
{
    ListNode * p;
    
    p = head->next;     // 指向第一个有效节点
    
    while (p != NULL) {
        if (p->data != e)
            p = p->next;
        else
            break;
    }
    return p;
}
/**
 * 定位操作。
 * 查找线性表中元素值为 e 的元素，查找成功将对应元素的序号返回，否则返回 0，表示失败。
 */
int LocatePos(LinkList head, DataType e)
{
    ListNode * p;
    int j;
    
    if (ListEmpty(head))
        return 0;
    
    // 定位链表中的第一个节点
    p = head->next;
    j = 1;
    
    while (p != NULL) {
        if (p->data != e) { // 如果该节点有效，且不为 e, 则查找下一个元素
            p = p->next;
            j++;
        } else {
            return j;
        }
    }
    
    if (! p)                // 链表中没有找到值为 e 的节点
        return 0;
}
/**
 * 插入操作
 * 在单链表中第 i 个位置插入一个结点，结点的元素值为 e。插入成功返回 1，失败返回 0 。
 * 有两点需要注意:
 *  1. 必须要找到第 i 个节点的前一个节点
 *  2. 插入位置不能超过链表长度 + 1
 */
int InsertList(LinkList head, int i, DataType e)
{
    ListNode * p, * pre;
    int j;
    
    // 因为有可能插入到第一个有效节点位置，而第一个有效节点的前一个节点是头结点，所以从头结点开始定位。
    // pre 和 j 都是要定位到第 i 个节点的前一个节点 i - 1
    pre = head;
    j = 0;
    
    while (pre->next != NULL && j < i - 1) {    // 直到找到第 i - 1 个结点
        pre = pre->next;
        j++;
    }
    if (j != i - 1) {
        printf("插入位置错误\n");
        return 0;
    }
    
    if ((p = (ListNode*)malloc(sizeof(ListNode))) == NULL) {
        exit(-1);
    }
    
    p->data = e;
    p->next = pre->next;
    pre->next = p;
    
    return 1;
}
/**
 * 删除操作
 * 删除单链表中的第 i 个位置的节点。删除成功返回 1，失败返回 0
 * 有两点需要注意:
 *  1. 必须要找到第 i 个节点的前一个节点
 *  2. 删除位置必须存在
 */
int DeleteList(LinkList head, int i, DataType * e)
{
    ListNode * pre, * p;
    int j;
    
    // 仍然要从头结点开始定位起。
    pre = head;
    j = 0;
    
    while (pre->next != NULL && j < i - 1) {
        pre = pre->next;
        j++;
    }
    if (j != i - 1) {
        printf("删除位置错误\n");
        return 0;
    }
    
    p = pre->next;
    *e = p->data;
    pre->next = p->next;
    free(p);
    
    return 1;
}
/**
 * 求表长操作
 */
int ListLength(LinkList head)
{
    ListNode * p;
    int count;
    
    // 指向第一个有效节点
    p = head->next;
    count = 0;
    
    while (p != NULL) {
        p = p->next;
        count++;
    }
    return count;
}

void DestroyList(LinkList head)
{
    ListNode * p, * q;
    
    p = head;
    
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
}