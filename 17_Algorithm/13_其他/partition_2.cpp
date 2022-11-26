
#include <stdio.h>

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int pivot_index = high;
    while (low < high) {
        while (low < high && a[low] <= pivot)
            low++;
        while (low < high && a[high] >= pivot)
            high--;
        if (low < high) {
            swap(a, low, high);
        }
    }
    if (high != pivot_index) {
        swap(a, high, pivot_index);
    }

    return high;
}

int main()
{
    int a[] = { 1, 2, 7, 8, 3, 4, 5, 9 };
    int len = sizeof(a) / sizeof(int);
    int val = 6;

    int *copy = new int[len + 1];
    for (int i = 0; i < len; i++) {
        copy[i] = a[i];
    }
    copy[len] = val;

    int pi = partition(copy, 0, len);
    printf("pi=%d\n", pi);
    for (int i = 0; i < pi; i++) {
        printf("%d ", copy[i]);
    }
    printf("\n");
    for (int i = pi + 1; i < len + 1; i++) {
        printf("%d ", copy[i]);
    }
    printf("\n");

    delete[] copy;

    return 0;
}