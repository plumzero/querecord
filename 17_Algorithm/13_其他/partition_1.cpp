
#include <stdio.h>

// 使 <= val 的位于左边，使 >= val 的位于右边
// val 可能并不是数组中的一个元素，怎么办呢？我们可以尝试将 val 添加到数组 a[] 的末尾，作为它的一个元素
int partition(int a[], int low, int high)
{
    int pivot = a[high];
    while (low < high) {
        while (low < high && a[low] <= pivot)
            low++;
        a[high] = a[low];
        while (low < high && a[high] >= pivot)
            high--;
        a[low] = a[high];
    }
    a[high] = pivot;

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