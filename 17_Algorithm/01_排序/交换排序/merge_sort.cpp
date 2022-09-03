
// 稳定排序

#include <stdio.h>

void merge(int a[], int start, int end, int* copy)
{
    if (start == end)
        return ;
    
    int mid = start + (end - start) / 2;
    merge(a, start, mid, copy);
    merge(a, mid + 1, end, copy);

    int i = start;
    int j = mid + 1;
    int k = start;
    
    while (i <= mid && j <= end)
        copy[k++] = (a[i] <= a[j] ? a[i++] : a[j++]);   // 注意，必须 a[i] <= a[j] 才能达成稳定排序
    while (i <= mid)
        copy[k++] = a[i++];
    while (j <= end)
        copy[k++] = a[j++];
    
    // 下面等价于 memcpy(&a[start], &copy[start], sizeof(int) * (end - start + 1))
    for (int i = start; i <= end; i++) {
        a[i] = copy[i];
    }
}

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    int len = sizeof(a) / sizeof(int);
    int copy[len] = { 0 };

    merge(a, 0, len - 1, copy);

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}