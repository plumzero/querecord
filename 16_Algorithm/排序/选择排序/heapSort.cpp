
#include <stdio.h>

void adjustHeap(int a[], int s, int n)  /** s 为父母结点索引 */
{
    int j;
    
    int ele;
    
    ele = a[s];
    for (j = 2 * s + 1; j <= n; j = j * 2 + 1) {
        if (j < n && a[j] < a[j + 1])
            j++;    /** j 为关键字较大的结点的下标 */
        if (ele > a[j])
            break;
        a[s] = a[j];
        s = j;
    }
    a[s] = ele;     /** 将子结点替换为根结点 */
}

void createHeap(int a[], int n)     /** n 为数组元素最大下标 */
{
    int i;
    for (i = (n - 1) / 2; i >= 0; i--) {
        adjustHeap(a, i, n);
    }
}

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
    
    int ele;
    int i;
    
    createHeap(a, sizeof(a) / sizeof(a[0]) - 1);
    
    for (i = sizeof(a) / sizeof(a[0]) - 1; i > 0; i--) { /** 将堆顶元素与最后一个元素交换，重新调整堆 */
        ele = a[0];
        a[0] = a[i];
        a[i] = ele;
        adjustHeap(a, 0, i - 1);
    }

    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}