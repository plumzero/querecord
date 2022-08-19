
#include <stdio.h>

void select_sort(int* a, int len)
{
    int ele;
    for (int i = 0; i < len - 1; i++) {
        int j = i;
        for (int k = i + 1; k < len; k++) {
            if (a[j] > a[k])
                j = k;
        }
        if (i != j) {
            ele = a[i];
            a[i] = a[j];
            a[j] = ele;
        }
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };

    select_sort(a, sizeof(a)/sizeof(int));

    return 0;
}