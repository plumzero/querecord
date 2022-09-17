
// 03 2
// 不修改数组找出重复的数字

// 问题:
// 在一个长度为 n+1 的数组里的所有数字都在 1~n 的范围内，所以数组中至少有一个数字是重复的。
// 请找出数组中任意一个重复的数字，但不能修改输入的数组。
// 例如，如果输入长度为 8 的数组 { 2, 3, 5, 4, 3, 2, 6, 7 }, 那么重复的数字是 2 或者 3 。

// 分析:
// 采用二分法，分别统计左右两部分元素在数组中出现的个数之和。若和大于该部分元素长度，则重复
// 元素在该部分内。重复二分查找过程..., 直到收敛于某一个元素(start == end)

#include <stdio.h>

int count_range(int a[], int len, int start, int end)
{
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] >= start && a[i] <= end)
            count++;
    }

    return count;
}

bool dup_in_array_no_edit(int a[], int len, int* dup)
{
    // assert(a != nullptr && len > 0);
    // assert(a[i] > 0 && a[i] < len);

    //注意: start 和 end 不是数组下标，而是每次查找数组元素的值的范围
    int start = 1;
    int end = len - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        int count = count_range(a, len, start, mid);
        if (start == end) {
            if (count > 1) {
                *dup = start;
                return true;
            }
        }
        if (count > mid - start + 1) {
            end = mid;  // 在进行二分时，并没有排除中间元素，所以必须要在 while 循环内部返回，否则会死循环
        } else {
            start = mid + 1;
        }
    }

    return false;
}

int main()
{
    {
        int a[] = { 2, 3, 5, 4, 3, 2, 6, 7 };
        int len = sizeof(a) / sizeof(int);

        int dup;
        if (dup_in_array_no_edit(a, len, &dup)) {
            printf("dup=%d\n", dup);
        }
    }

    {
        int a[] = { 1, 2, 3, 4, 5, 6, 7, 7 };
        int len = sizeof(a) / sizeof(int);

        int dup;
        if (dup_in_array_no_edit(a, len, &dup)) {
            printf("dup=%d\n", dup);
        }
    }

    return 0;
}