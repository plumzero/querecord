
#include <stdio.h>

void bin_insert_sort(int* a, int len)
{
    for (int i = 1; i < len; i++) {
        int j = i - 1;
        int ele = a[i];
        int low = 0, high = j, mid;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (ele >= a[mid])
                low = mid + 1;
            else
                high = mid - 1;
        }

        for (j = i; j > low; j--) {
            a[j] = a[j - 1];
        }
        a[low] = ele;
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void bin_insert_sort_desc(int* a, int len)
{
    for (int i = 1; i < len; i++) {
        int j = i - 1;
        int ele = a[i];
        int low = 0, high = j, mid;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (ele > a[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }

        for (j = i; j > low; j--) {
            a[j] = a[j - 1];
        }
        a[low] = ele;
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    {
        int a[] = { 3, 1, 4, 1, 5, 9, 2, 3, 6, 3 };
        bin_insert_sort(a, sizeof(a)/sizeof(int));
    }

    {
        int a[] = { 3, 1, 4, 1, 5, 9, 2, 3, 6, 3 };
        // int a[] = { 3, 1, 4 };
        bin_insert_sort_desc(a, sizeof(a)/sizeof(int));
    }

    return 0;
}