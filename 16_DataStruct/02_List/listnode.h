
// 仅作测试，对输入异常不作严格判断

#include <stdio.h>
#include <stdarg.h>

typedef struct ListNode {
    int val;
    ListNode* next;
} ListNode;

ListNode* create_node(int val)
{
    ListNode* node = new ListNode();
    node->val = val;
    node->next = nullptr;

    return node;
}

void connect_node(ListNode* node1, ListNode* node2)
{
    // assert(node1 != nullptr);
    node1->next = node2;
}

void print_list(ListNode* head) {
    ListNode* pNode = head;
    while (pNode) {
        printf("%d ", pNode->val);
        pNode = pNode->next;
    }
    printf("\n");
}

ListNode* create_list(int n, ...)
{
    // assert(n >= 0);
    ListNode* head = nullptr;
    ListNode* pPre = nullptr;

    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++) {
        int val = va_arg(args, int);
        ListNode* pNode = create_node(val);
        if (head == nullptr) {
            head = pNode;
            pPre = pNode;
        } else {
            pPre->next = pNode;
            pPre = pNode;
        }
    }

    va_end(args);

    return head;
}

void destroy_list(ListNode** head)
{
    ListNode* pNode = *head;
    while (pNode) {
        ListNode* pNext = pNode->next;
        delete pNode;
        pNode = nullptr;
        pNode = pNext;
    }

    *head = nullptr;
}
