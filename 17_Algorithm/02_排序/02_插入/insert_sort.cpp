
// 稳定排序

// 每次取出一个元素，将取出元素与已排序元素进行比较。由于最先取出的元素不必比较，所以外层一共循环 len - 1 次

// 假设已排序列中有 i 个元素，则将后面索引为 i 的元素取出，分别与这 i 个元素进行比较，这就是内层比较循环


#include <stdio.h>

void insert_sort(int a[], int len)
{
    for (int i = 1; i < len; i++) {
        int ele = a[i];
        int j;
        for (j = i - 1; j >= 0; j--) {
            if (a[j] > ele) {
                a[j + 1] = a[j];    // 后移
            } else {
                break;          // 加快速度
            }
        }
        a[j + 1] = ele;
    }
}

void insert_sort_desc(int* a, int len)
{
    for (int i = 1; i < len; i++) {
        int ele = a[i];
        int j;
        for (j = i - 1; j >= 0; j--) {
            if (a[j] < ele) {
                a[j + 1] = a[j];    // 后移
            } else {
                break;          // 加快速度
            }
        }
        a[j + 1] = ele;
    }
}

int main()
{
    {
        int a[] = { 3, 1, 4, 1, 5, 9, 2, 6 };
        int len = sizeof(a) / sizeof(int);

        insert_sort(a, len);

        for (int i = 0; i < len; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    {
        int a[] = { 3, 1, 4, 1, 5, 9, 2, 6 };
        int len = sizeof(a) / sizeof(int);

        insert_sort_desc(a, len);

        for (int i = 0; i < len; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    return 0;
}