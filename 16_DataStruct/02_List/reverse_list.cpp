
// 24 反转链表

// 问题:
// 输入一个链表的头节点，反转该链表并输出反转后链表的头节点

// 分析:
// 略

#include <stdio.h>
#include "listnode.h"

ListNode* reverse_list(ListNode* pHead)
{
    // assert(pHead != nullptr);

    ListNode* pNode = pHead;
    ListNode* preNode = nullptr;
    while (pNode) {
        ListNode* pNext = pNode->next;
        pNode->next = preNode;
        preNode = pNode;
        pNode = pNext;
    }

    return preNode;
}

// 分析二:
// 尝试使用递归
ListNode* reverse_list2(ListNode* pNode, ListNode* pOldHead, ListNode** pNewHead)
{
    if (pNode->next == nullptr) { // 找到尾节点后返回
        *pNewHead = pNode;
        return pNode;
    }
    
    ListNode* node = reverse_list2(pNode->next, pOldHead, pNewHead);
    node->next = pNode;
    if (pNode == pOldHead) {     // 旧的头节点 next 域要指向 null
        pNode->next = nullptr;
    }

    return pNode;
}

int main()
{
    {
        ListNode* node1 = create_list(6, 11, 22, 33, 44, 55, 66);

        ListNode* node2 = reverse_list(node1);

        print_list(node2);
        destroy_list(&node2);
    }

    {
        ListNode* node1 = create_list(6, 11, 22, 33, 44, 55, 66);

        ListNode* pNewHeader = nullptr;
        reverse_list2(node1, node1, &pNewHeader);

        print_list(pNewHeader);
        destroy_list(&pNewHeader);   
    }

    return 0;
}