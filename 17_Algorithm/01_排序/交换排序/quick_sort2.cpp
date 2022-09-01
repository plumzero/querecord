
// 第二种方法

#include <stdio.h>

// 降序排列的话，只需要改为 pivot >= a[high] 和 pivot <= a[low] 即可

// 返回分区后枢轴索引
int partition(int a[], int low, int high)
{
    int pivot = a[low];
    int start = low;
    while (low < high) {
        while (low < high && pivot <= a[high])  // 也必须先从后开始
            high--;
        while (low < high && pivot >= a[low])
            low++;
        if (low < high) {
            int tmp = a[low];
            a[low] = a[high];
            a[high] = tmp;
        }
    }
    if (start != low) {
        int tmp = a[start];
        a[start] = a[low];
        a[low] = tmp;
    }

    return low;
}

void quick_sort(int a[], int len, int low, int high)
{
    if (low < high) {
        int index = partition(a, low, high);
        quick_sort(a, len, low, index - 1);
        quick_sort(a, len, index + 1, high);
    }
}

// 不考虑异常传值
int main()
{
    int a[] = { 3, 2, 4, 6, 2, 8, 3, 7, 1 };

    int len = sizeof(a) / sizeof(int);

    quick_sort(a, len, 0, len - 1);

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}