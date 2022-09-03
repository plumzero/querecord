
// 利用归排求逆序对

#include <stdio.h>

int merge(int a[], int start, int end, int* copy)
{
    if (start == end)
        return 0;
    
    int mid = start + (end - start) / 2;
    int left_count = merge(a, start, mid, copy);
    int right_count = merge(a, mid + 1, end, copy);

    int i = start;
    int j = mid + 1;
    int k = start;
    
    int count = 0;

    while (i <= mid && j <= end) {
        if (a[i] <= a[j]) {
            copy[k++] = a[i++];
        } else {
            copy[k++] = a[j++];
            count += mid - i + 1;       // 与归排比较，多了这句代码
        }
    }
    while (i <= mid)
        copy[k++] = a[i++];
    while (j <= end)
        copy[k++] = a[j++];
    
    for (int i = start; i <= end; i++) {
        a[i] = copy[i];
    }

    return left_count + right_count + count;
}

int main()
{
    // int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    // int a[] = { 7, 5, 6, 4 };
    int a[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    int len = sizeof(a) / sizeof(int);
    int copy[len] = { 0 };

    int count = merge(a, 0, len - 1, copy);

    printf("count = %d\n", count);
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}