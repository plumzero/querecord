
// 22 链表中倒数第 k 个节点

// 问题: 输入一个链表，输出该链表中倒数第 k 个节点。
// 例如一个链表有 6 个节点，从头节点开始，它们的值依次是 1 2 3 4 5 6 。这个链表的倒数
// 第 3 个节点是值为 4 的节点

// 分析:
// 定义两个指针 pa 和 pb 同时指向头节点，pa 指针先走 k-1 步，之后 pb 也开始遍历，始终保持
// 两个指针间隔为 k-1 步，当 pa 指针到达尾节点时，pb 指向的节点即为倒数第 k 个节点。
// 注意链表长度小于 k 的情况

#include <stdio.h>

#include "listnode.h"

ListNode* kth_from_end(ListNode* pHead, int k)
{
    // assert(pHead != nullptr && k > 0);

    ListNode *pa, *pb;
    pa = pb = pHead;

    for (int i = 1; i < k; i++) {
        if (pa->next == nullptr)    // 没走完 k-1 步就已经到达了尾节点
            return nullptr;
        pa = pa->next;
    }

    while (pa->next != nullptr) {
        pa = pa->next;
        pb = pb->next;
    }

    return pb;
}

int main()
{
    {
        ListNode* head = create_list(6, 11, 22, 33, 44, 55, 66);
        ListNode* node = kth_from_end(head, 1);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }
        destroy_list(&head);
    }

    {
        ListNode* head = create_list(6, 11, 22, 33, 44, 55, 66);
        ListNode* node = kth_from_end(head, 3);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }
        destroy_list(&head);
    }

    {
        ListNode* head = create_list(6, 11, 22, 33, 44, 55, 66);
        ListNode* node = kth_from_end(head, 6);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }
        destroy_list(&head);
    }

    {
        ListNode* head = create_list(6, 11, 22, 33, 44, 55, 66);
        ListNode* node = kth_from_end(head, 7);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }
        destroy_list(&head);
    }

    {
        ListNode* head = create_list(1, 11);
        ListNode* node = kth_from_end(head, 2);
        if (node != nullptr) {
            printf("%d\n", node->val);
        }
        destroy_list(&head);
    }

    return 0;
}