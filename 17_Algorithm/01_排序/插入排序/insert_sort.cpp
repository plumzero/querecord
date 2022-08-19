
#include <stdio.h>

void insert_sort(int* a, int len)
{
    for (int i = 1; i < len; i++) {
        int j = i - 1;
        int ele = a[i];
        while (j >= 0 && a[j] > ele) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = ele;
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void insert_sort_desc(int* a, int len)
{
    for (int i = 1; i < len; i++) {
        int j = i - 1;
        int ele = a[i];
        while (j >= 0 && a[j] < ele) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = ele;
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    {
        int a[] = { 3, 1, 4, 1, 5, 9, 2, 6 };

        insert_sort(a, sizeof(a)/sizeof(int));
    }

    {
        int a[] = { 3, 1, 4, 1, 5, 9, 2, 6 };

        insert_sort_desc(a, sizeof(a)/sizeof(int));
    }

    return 0;
}