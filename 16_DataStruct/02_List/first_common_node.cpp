
// 52 两个链表的第一个公共节点

// 问题: 输入两个链表，找出它们的第一个公共节点。
// 例如如下的两个链表，其第一个公共节点的值是 6
// 1 -> 2 -> 3
//           ↓
//           6 -> 7
//           ↑
//      4 -> 5

// 分析:
// 依次遍历两个链表，得到各自的长度，计算长度的差值为 k 。长链表从头节点移动 k 步，之后
// 长, 短链表同时移动，直到遇到第一个公共节点为止。

// 关于代码优化:
// 1. 对于多次使用的操作，应该将其独立为一个函数，比如这里的获取链表的长度
// 2. 初版中的 k 可能为负值，在 for 循环的条件表达式中出现了 i < -k ，这样写没做，但不好


#include <stdio.h>
#include "listnode.h"

// 初版
ListNode* first_common_node(ListNode* pHead1, ListNode* pHead2)
{
    // assert(pHead1 != nullptr && pHead2 != nullptr);
    
    int len1 = 0;
    int len2 = 0;
    
    ListNode* pNode1 = pHead1;
    while (pNode1) {
        len1++;
        pNode1 = pNode1->next;
    }
    
    ListNode* pNode2 = pHead2;
    while (pNode2) {
        len2++;
        pNode2 = pNode2->next;
    }
    
    int k = len1 - len2;
    if (k >= 0) {
        pNode1 = pHead1;
        pNode2 = pHead2;
        for (int i = 0; i < k; i++) {
            pNode1 = pNode1->next;
        }
    } else {
        pNode1 = pHead1;
        pNode2 = pHead2;
        for (int i = 0; i < -k; i++) {
            pNode2 = pNode2->next;
        }
    }
    
    while (pNode1 != pNode2) {
        pNode1 = pNode1->next;
        pNode2 = pNode2->next;
    }
    
    return pNode1;
}


// 二版
int list_len(ListNode* pHead)
{
    int len = 0;
    
    ListNode* pNode = pHead;
    while (pNode) {
        len++;
        pNode = pNode->next;
    }
    
    return len;
}

ListNode* first_common_node2(ListNode* pHead1, ListNode* pHead2)
{
    // assert(pHead1 != nullptr && pHead2 != nullptr);
    
    int len1 = list_len(pHead1);
    int len2 = list_len(pHead2);
    
    ListNode* pLong = pHead1;
    ListNode* pShort = pHead2;
    int diff = len1 - len2;
    if (len1 < len2) {
        pLong = pHead2;
        pShort = pHead1;
        diff = len2 - len1;
    }
    
    for (int i = 0; i < diff; i++) {
        pLong = pLong->next;
    }
    
    while (pLong != pShort) {
        pLong = pLong->next;
        pShort = pShort->next;
    }
    
    return pLong;
}

int main()
{
    {
        ListNode* node1 = create_node(1);
        ListNode* node2 = create_node(2);
        ListNode* node3 = create_node(3);
        ListNode* node4 = create_node(4);
        ListNode* node5 = create_node(5);
        ListNode* node6 = create_node(6);
        ListNode* node7 = create_node(7);

        connect_node(node1, node2);
        connect_node(node2, node3);
        connect_node(node3, node6);
        connect_node(node6, node7);
        connect_node(node4, node5);
        connect_node(node5, node6);

        ListNode* node = first_common_node(node1, node4);
        if (node) {
            printf("%d\n", node->val);
        }
    }

    {
        ListNode* node1 = create_node(1);
        ListNode* node2 = create_node(2);
        ListNode* node3 = create_node(3);
        ListNode* node4 = create_node(4);
        ListNode* node5 = create_node(5);
        ListNode* node6 = create_node(6);
        ListNode* node7 = create_node(7);

        connect_node(node1, node2);
        connect_node(node2, node3);
        connect_node(node3, node6);
        connect_node(node6, node7);
        connect_node(node4, node5);
        connect_node(node5, node6);

        ListNode* node = first_common_node2(node1, node4);
        if (node) {
            printf("%d\n", node->val);
        }
    }

    {
        ListNode* node1 = create_node(1);
        ListNode* node2 = create_node(2);
        ListNode* node3 = create_node(3);
        ListNode* node4 = create_node(4);
        ListNode* node5 = create_node(5);
        ListNode* node6 = create_node(6);
        ListNode* node7 = create_node(7);

        connect_node(node1, node2);
        connect_node(node2, node3);
        connect_node(node3, node6);
        connect_node(node6, node7);
        connect_node(node4, node5);
        connect_node(node5, node6);

        ListNode* node = first_common_node2(node4, node1);
        if (node) {
            printf("%d\n", node->val);
        }
    }

    {
        ListNode* node = first_common_node2(nullptr, nullptr);
        if (node) {
            printf("%d\n", node->val);
        }
    }

    {
        ListNode* node1 = create_node(1);
        ListNode* node = first_common_node2(node1, nullptr);
        if (node) {
            printf("%d\n", node->val);
        }
    }

    {
        ListNode* node1 = create_node(1);
        ListNode* node = first_common_node2(nullptr, node1);
        if (node) {
            printf("%d\n", node->val);
        }
    }

    return 0;
}