
// 问题: 求无序序列中第 k 大的元素

// 什么是第 k 大?
// 比如序列 4 1 3 2 中，第 1 大元素为 4，第 2 大元素为 3

// 分析:
// 将序列按照降序排序，那么排序后索引为 k-1 的元素就是第 k 大元素。
// 不过这里没有必要将所有的元素全部排序，可以这样:
// 先选定一个枢轴元素，将序列分成两部分，左侧部分不小于枢轴元素，右侧部分不大于枢轴元素。
//  如果枢轴元素索引等于 k-1, 就返回该枢轴元素。
//  如果枢轴元素索引大于 k-1, 那么第 k 大元素在左侧部分。
//  如果枢轴元素索引小于 k-1, 那么第 k 大元素在右侧部分。

#include <stdio.h>

int partion2(int a[], int low, int high)
{
    int pivot = a[low];
    while (low < high) {
        while (low < high && a[high] <= pivot)
            high--;
        a[low] = a[high];
        while (low < high && a[low] >= pivot)
            low++;
        a[high] = a[low];
    }
    a[low] = pivot;

    return low;
}

int kth(int a[], int low, int high, int k)
{
    int index = partion2(a, low, high);
    if (index == k - 1) {
        return a[index];
    } else if (index > k - 1) {
        return kth(a, low, index - 1, k);
    } else {
        return kth(a, index + 1, high, k);
    }
}

int main()
{
    int a[] = { 100, 200, 50, 23, 300, 560, 789, 456, 123, 258 };
    int len = sizeof(a) / sizeof(int);

    int k = 3;
    printf("%d: %d\n", k, kth(a, 0, len - 1, k));

    return 0;    
}