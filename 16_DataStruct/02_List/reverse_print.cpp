
// 06 从尾到头打印链表

// 问题:
// 输入一个链表的头节点，从尾到头反过来打印出每个链表的值。

// 分析一:
// 使用栈

#include <stdio.h>
#include <stack>

#include "listnode.h"

void reverse_print(ListNode* pHead)
{
    if (pHead != nullptr) {
        std::stack<ListNode*> _stack;
        ListNode* pNode = pHead;
        while (pNode) {
            _stack.push(pNode);
            pNode = pNode->next;
        }

        while (_stack.size() > 0) {
            pNode = _stack.top();
            _stack.pop();
            printf("%d ", pNode->val);
        }
        printf("\n");
    }
}

// 分析二:
// 既然用栈了，也可以尝试递归
void reverse_print2(ListNode* pHead)
{
    if (pHead != nullptr) {
        reverse_print2(pHead->next);
        printf("%d ", pHead->val);
    }
}

int main()
{
    {
        ListNode* head = create_list(6, 11, 22, 33, 44, 55, 66);
        reverse_print(head);
        destroy_list(&head);
    }

    {
        ListNode* head = create_list(6, 11, 22, 33, 44, 55, 66);
        reverse_print2(head);
        destroy_list(&head);
    }

    return 0;
}

