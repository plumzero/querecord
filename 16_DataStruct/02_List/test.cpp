
#include "listnode.h"

int main()
{
    ListNode* head = create_list(6, 11, 22, 33, 44, 55, 66);

    print_list(head);

    destroy_list(&head);

    if (head == nullptr) {
        printf("ok\n");
    }

    return 0;
}