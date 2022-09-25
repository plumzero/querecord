
// 25 合并两个排序的链表

// 问题:
// 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
// 例如下面的两个链表:
//  1 -> 3 -> 5 -> 7
//  2 -> 4 -> 6 -> 8
// 合并后的链表为:
// 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8

// 分析:
// 略

#include <stdio.h>
#include "listnode.h"

ListNode* merge_sort_list(ListNode* pHead1, ListNode* pHead2)
{
    ListNode* p1 = pHead1;
    ListNode* p2 = pHead2;
    ListNode* pNode = nullptr;
    ListNode* pHead = nullptr;

    while (p1 && p2) {
        if (p1->val > p2->val) {
            if (pHead == nullptr) {
                pHead = p2;
            } else {
                pNode->next = p2;
            }
            pNode = p2;
            p2 = p2->next;
        } else {
            if (pHead == nullptr) {
                pHead = p1;
            } else {
                pNode->next = p1;
            }
            pNode = p1;
            p1 = p1->next;
        }
    }

    while (p1) {
        if (pHead == nullptr)
            pHead = p1;
        else {
            pNode->next = p1;
        }
        pNode = p1;
        p1 = p1->next;
    }

    while (p2) {
        if (pHead == nullptr)
            pHead = p2;
        else {
            pNode->next = p2;
        }
        pNode = p2;
        p2 = p2->next;
    }

    return pHead;
}

// 分析二:
// 尝试递归

ListNode* merge_sort_list2(ListNode* pNode1, ListNode* pNode2)
{
    if (pNode1 == nullptr)
        return pNode2;
    if (pNode2 == nullptr)
        return pNode1;
    
    ListNode* merged = nullptr;

    if (pNode1->val > pNode2->val) {
        merged = pNode2;
        merged->next = merge_sort_list2(pNode1, pNode2->next);
    } else {
        merged = pNode1;
        merged->next = merge_sort_list2(pNode1->next, pNode2);
    }

    return merged;
}

int main()
{
    {
        ListNode* head1 = create_list(4, 1, 3, 5, 7);
        ListNode* head2 = create_list(4, 2, 4, 6, 8);
        ListNode* head = merge_sort_list(head1, head2);
        print_list(head);
        destroy_list(&head);
    }

    {
        ListNode* head1 = create_list(4, 1, 3, 5, 7);
        ListNode* head = merge_sort_list(head1, nullptr);
        print_list(head);
        destroy_list(&head);
    }

    {
        ListNode* head2 = create_list(4, 2, 4, 6, 8);
        ListNode* head = merge_sort_list(nullptr, head2);
        print_list(head);
        destroy_list(&head);
    }

    {
        ListNode* head = merge_sort_list(nullptr, nullptr);
        print_list(head);
        destroy_list(&head);
    }

    {
        ListNode* head1 = create_list(4, 1, 3, 5, 7);
        ListNode* head2 = create_list(4, 2, 4, 6, 8);
        ListNode* head = merge_sort_list2(head1, head2);
        print_list(head);
        destroy_list(&head);
    }

    {
        ListNode* head1 = create_list(4, 1, 3, 5, 7);
        ListNode* head = merge_sort_list2(head1, nullptr);
        print_list(head);
        destroy_list(&head);
    }

    {
        ListNode* head2 = create_list(4, 2, 4, 6, 8);
        ListNode* head = merge_sort_list2(nullptr, head2);
        print_list(head);
        destroy_list(&head);
    }

    {
        ListNode* head = merge_sort_list2(nullptr, nullptr);
        print_list(head);
        destroy_list(&head);
    }

    return 0;
}