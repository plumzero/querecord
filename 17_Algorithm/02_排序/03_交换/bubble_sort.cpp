

// 稳定排序

// 以升序排序为例
// 与简单选择排序类似，冒泡排序每次循环的排序结果是将剩余元素中最大值放在最后一个索引上，最后剩余的一个元素肯定
// 是最小值，直接放在第一个索引上，不必排序。所以冒泡排序的外层循环也是 len - 1 次

// 关于内层比较循环，与简单选择排序不同，冒泡排序是元素互相之间进行比较，将二者中较小的元素放在最前面
// 两两比较时，每次比较循环次数是剩余元素个数减 1

// 冒泡排序中的序列，是局部有序序列，内层循环可以通过折半方法提高排序速度

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


void bubble_sort(int a[], int len)
{
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) { // 熟悉的 len - 1 - i
            if (a[j] > a[j + 1]) {
                swap(a, j, j + 1);
            }
        }
    }
}

void bubble_sort_youhua(int a[], int len)
{
    for (int i = 0; i < len - 1; i++) {
        bool swapped = false;          // 局部有序时可提高排序速度
        for (int j = 0; j < len - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a, j, j + 1);
                swapped = true;
            }
        }
        if (! swapped) {
            break;
        }
    }
}

void bubble_sort_2(int a[], int len)
{
    for (int i = len - 1; i > 0; i--) { // 代码上更简洁一些
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a, j, j + 1);
            }
        }
    }
}

void bubble_sort_2_youhua(int a[], int len)
{
    for (int i = len - 1; i > 0; i--) {
        bool swapped = false;
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a, j, j + 1);
                swapped = true;
            }
        }
        if (! swapped) {
            break;
        }
    }
}

int main()
{
    {
        int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
        int len = sizeof(a) / sizeof(int);

        bubble_sort(a, len);

        print(a, len);
    }

    {
        int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
        int len = sizeof(a) / sizeof(int);

        bubble_sort_youhua(a, len);

        for (int i = 0; i < len; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    {
        int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
        int len = sizeof(a) / sizeof(int);

        bubble_sort_2(a, len);

        for (int i = 0; i < len; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    {
        int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };
        int len = sizeof(a) / sizeof(int);

        bubble_sort_2_youhua(a, len);

        for (int i = 0; i < len; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    return 0;
}