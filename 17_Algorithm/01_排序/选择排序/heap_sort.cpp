
// 堆排序

#include <stdio.h>

void adjust_heap(int a[], int i, int n);

// 索引从 0 开始

// 建堆
void create_heap(int a[], int n)
{
    for (int i = (n - 1) / 2; i >= 0; i--) {
        adjust_heap(a, i, n);
    }
}

// 调整堆
void adjust_heap(int a[], int s, int n) // s 为父母节点索引
{
    int ele = a[s];
    for (int j = 2 * s + 1; j <= n; j = 2 * j + 1) {
        if (j < n && a[j] < a[j + 1])
            j++;
        if (ele > a[j])
            break;
        a[s] = a[j];
        s = j;
    }
    a[s] = ele;
}

void heap_sort(int a[], int len)
{
    create_heap(a, len - 1);

    for (int i = len - 1; i > 0; i--) {     // 将堆顶元素与最后一个元素交换，重新调整堆
        int ele = a[0];
        a[0] = a[i];
        a[i] = ele;
        adjust_heap(a, 0, i - 1);
    }
}

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    int len = sizeof(a) / sizeof(int);

    heap_sort(a, len);

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}