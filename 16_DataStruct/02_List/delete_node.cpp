
// 18 1 删除链表的节点

// 问题:
// 给定单向链表的头指针和一个节点指针，定义一个函数在 O(1) 时间内删除该节点

// 分析:
// 将该节点指针的下一个节点内容复制到该节点，之后删除下一个节点
// 注意对特殊节点的处理

#include <stdio.h>

#include "listnode.h"

void delete_node(ListNode** pHead, ListNode* node)
{
    // assert(pHead != nullptr && *pHead != nullptr);
    
    // 头节点
    if (*pHead == node) {
        *pHead = node->next;
        delete node;
        node = nullptr;
        return ;
    }
    // 尾节点
    if (node->next == nullptr) {
        ListNode* pNode = *pHead;
        ListNode* preNode = nullptr;
        while (pNode->next) {
            preNode = pNode;
            pNode = pNode->next;
        }
        preNode->next = nullptr;
        delete pNode;
        pNode = nullptr;
        return ;
    }
    // 中间节点
    ListNode* pNext = node->next;
    node->val = pNext->val;
    node->next = pNext->next;
    delete pNext;
    pNext = nullptr;
    return ;
}

int main()
{
    // 只有一个节点
    {
        ListNode* node1 = create_node(11);

        delete_node(&node1, node1);

        print_list(node1);
        destroy_list(&node1);
    }

    // 删除头节点
    {
        ListNode* node1 = create_node(11);
        ListNode* node2 = create_node(22);
        ListNode* node3 = create_node(33);

        connect_node(node1, node2);
        connect_node(node2, node3);

        delete_node(&node1, node1);

        print_list(node1);
        destroy_list(&node1);
    }

    // 删除尾节点
    {
        ListNode* node1 = create_node(11);
        ListNode* node2 = create_node(22);
        ListNode* node3 = create_node(33);

        connect_node(node1, node2);
        connect_node(node2, node3);

        delete_node(&node1, node3);

        print_list(node1);
        destroy_list(&node1);
    }

    // 删除中间节点
    {
        ListNode* node1 = create_node(11);
        ListNode* node2 = create_node(22);
        ListNode* node3 = create_node(33);

        connect_node(node1, node2);
        connect_node(node2, node3);

        delete_node(&node1, node2);

        print_list(node1);
        destroy_list(&node1);
    }

    return 0;
}