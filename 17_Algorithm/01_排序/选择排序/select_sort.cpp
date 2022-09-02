
// 稳定排序

// 以升序排序为例，在简单选择排序中，每次循环时要选择一个剩余值中最小的元素放在已排序元素的后面。
// 例如待排序列 3 1 2 4 , 第一次循环结果将 1 放在索引 0 上，第二次循环结果将 2 放在索引 1 上，第
// 三次循环结果将 3 放在索引 2 上，而最后一个元素 4 肯定是最大值，将其直接放在最后的索引 3 上，不必
// 再循环。所以整个循环次数应该是 len - 1, 其中 len 为待排元素个数

// 内层比较循环没有什么好说的

#include <stdio.h>

void select_sort(int* a, int len)
{
    int ele;
    for (int i = 0; i < len - 1; i++) {
        int j = i;
        for (int k = i + 1; k < len; k++) { // 只需要记录最小值的索引就行了
            if (a[j] > a[k])                // 比较过程中并不需要排序，因为每次比较是为了找出剩余最小值所在的索引
                j = k;
        }
        if (i != j) {
            ele = a[i];
            a[i] = a[j];
            a[j] = ele;
        }
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int a[] = { 56, 22, 67, 32, 59, 12, 89, 26, 48, 37 };

    select_sort(a, sizeof(a)/sizeof(int));

    return 0;
}