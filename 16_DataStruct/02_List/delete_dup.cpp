
// 18 2 删除链表中重复的节点

// 问题:
// 在一个排序的链表中，如何删除重复的节点?
// 例如，链表 1 -> 2 -> 3 -> 3 -> 5 ，删除重复节点后为 1 -> 2 -> 5

// 分析:
// 遍历链表中的每个节点。在遍历到某个节点时，并判断当前节点与下一个节点值是否相等。
// 如果不相等，则继续遍历；如果相等，则记录节点值，依次遍历后面的元素，将与记录值
// 相同的节点删除，直到节点值不相等。

#include <stdio.h>
#include "listnode.h"

void delete_dup(ListNode** pHead)
{
    // assert(pHead != nullptr && *pHead != nullptr);

    ListNode* pNode = *pHead;
    ListNode* preNode = nullptr;
    while (pNode) {
        if (pNode->next == nullptr) {
            pNode = pNode->next;
        } else if (pNode->val != pNode->next->val) {
            preNode = pNode;
            pNode = pNode->next;
        } else {
            int val = pNode->val;
            while (pNode != nullptr && pNode->val == val) {
                ListNode* pNext = pNode->next;
                delete pNode;
                pNode = nullptr;
                pNode = pNext;
            }
            if (preNode == nullptr) {
                *pHead = pNode;
            } else {
                preNode->next = pNode;
            }
        }
    }
}

int main()
{
    {
        ListNode* node1 = create_list(3, 11, 11, 22);

        delete_dup(&node1);

        print_list(node1);
        destroy_list(&node1);
    }

    {
        ListNode* node1 = create_list(4, 11, 11, 22, 22);

        delete_dup(&node1);
        
        print_list(node1);
        destroy_list(&node1);
    }

    {
        ListNode* node1 = create_list(3, 11, 22, 22);

        delete_dup(&node1);
        
        print_list(node1);
        destroy_list(&node1);
    }

    {
        ListNode* node1 = create_list(3, 11, 22, 33);

        delete_dup(&node1);
        
        print_list(node1);
        destroy_list(&node1);
    }

    return 0;
}