
#include <stdio.h>

void swap(int a[], int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void print(int a[], int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void select_sort(int a[], int len)
{
    for (int i = len - 1; i > 0; i--) {
        int max_index = 0;
        for (int j = 1; j <= i; j++) {
            if (a[j] > a[max_index]) {
                max_index = j;
            }
        }
        swap(a, i, max_index);
    }
}

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    int len = sizeof(a) / sizeof(int);

    select_sort(a, len);

    print(a, len);

    return 0;
}