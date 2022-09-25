
// 23 链表中环的入口节点

// 问题:
// 如果一个链表中包含环，如何找出环的入口节点？
// 例如在下面的链表中，环的入口节点是 3
//           +- - - - - - - +
//           ↓              ↑
// 1 -> 2 -> 3 -> 4 -> 5 -> 6

// 分析:
// 首先判断链表中是否存在环。定义两个指针，一快一慢进行移动，当慢指针追上快指针时则存在环。若快指针到达尾节点则不存在环
// 其次计算环中节点个数，假设为 k
// 最后定义两个指针从头节点开始，第一个指针先走 k 步，之后两个指针同时移动，两指针相等时的交点节点即为入口节点

#include <stdio.h>
#include "listnode.h"

ListNode* meet(ListNode* pHead)
{
    // assert(pHead != nullptr);

    ListNode* pSlow = pHead->next;
    if (pSlow == nullptr)
        return nullptr;
    
    ListNode* pFast = pSlow->next;
    while (pSlow != nullptr && pFast != nullptr) {
        if (pSlow == pFast)
            return pFast;
        pSlow = pSlow->next;
        pFast = pFast->next;
        if (pFast != nullptr)
            pFast = pFast->next;
    }

    return nullptr;
}

ListNode* entry_node(ListNode* pHead)
{
    ListNode* meeting_node = meet(pHead);
    if (meeting_node == nullptr)
        return nullptr;

    int k = 1;
    ListNode* pNode = meeting_node;
    while (pNode->next != meeting_node) {
        k++;
        pNode = pNode->next;
    }

    ListNode *p1, *p2;
    p1 = p2 = pHead;
    for (int i = 1; i <= k; i++) {
        p1 = p1->next;
    }

    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1;
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

        connect_node(node1, node2);
        connect_node(node2, node3);
        connect_node(node3, node4);
        connect_node(node4, node5);
        connect_node(node5, node6);
        connect_node(node6, node3);

        ListNode* node = entry_node(node1);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }

        // destroy_list(&node1);
    }

    {
        ListNode* node1 = create_node(1);

        connect_node(node1, node1);

        ListNode* node = entry_node(node1);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }

        // destroy_list(&node1);
    }

    {
        ListNode* node1 = create_node(1);
        ListNode* node2 = create_node(2);
        ListNode* node3 = create_node(3);
        ListNode* node4 = create_node(4);
        ListNode* node5 = create_node(5);

        connect_node(node1, node2);
        connect_node(node2, node3);
        connect_node(node3, node4);
        connect_node(node4, node5);

        ListNode* node = entry_node(node1);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }

        // destroy_list(&node1);
    }

    return 0;
}