
// 二分查找，是将有序序列的数据从中间分成前后两个子表，通过不断缩小目标值的检索范围进行检索的方法。

// 其步骤是:
// 1. 将序列中间的元素(如果序列的元素个数为偶数，则取左侧的元素)与目标值进行比较，执行相应动作
// 2. 在缩小后的范围内执行同样的操作，直至检索范围值缩小到 1

#include <stdio.h>

// 不考虑异常输入情况
// 成功返回索引，失败返回 -1
int binary_search(int a[], int len, int val)
{
    int low = 0, high = len - 1, mid;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (val >= a[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (a[mid] == val)
        return mid;
    else
        return -1;
}

int main()
{
    {
        int a[] = { 12, 22, 26, 32, 37, 48, 56, 59, 67, 89 };
        int len = sizeof(a) / sizeof(int);

        printf("%d\n", binary_search(a, len, 32));
    }

    {
        int a[] = { 12, 22, 26, 32, 37, 48, 56, 59, 67, 89 };
        int len = sizeof(a) / sizeof(int);

        printf("%d\n", binary_search(a, len, 55));
    }

    return 0;
}