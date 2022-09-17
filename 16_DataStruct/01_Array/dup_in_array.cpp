
// 03 1
// 数组中重复的数字

// 问题:
// 在一个长度为 n 的数组里的所有数字都在 0~n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
// 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
// 例如，如果输入长度为 7 的数组 { 2, 3, 1, 0, 2, 5, 3 }，那么对应的输出是重复的数字 2 或者 3

// 分析:
// 数组长度为 n, 数组中各元素的范围为 0~n-1。假设数组有序且不重复，则每个元素的值应与对应索引相等，现在有些
// 数组元素是相等的，那么在数组排序后至少有一个元素值的大小与对应索引不相等。
// 可以依次扫描数组中的每个元素，将这个元素放到对应的索引内存中。如果某个元素应该放置的索引内存已经存在相等元素，
// 则这个元素就是一个重复元素

#include <stdio.h>

bool duplication_in_array(int a[], int len, int* dup)
{
    // assert(a != nullptr && len > 0);
    // assert(a[i] >= 0 && a[i] < len)
    for (int i = 0; i < len; i++)
    {
        while (a[i] != i) {
            if (a[i] == a[a[i]]) {
                *dup = a[i];
                return true;
            }
            int tmp = a[i];
            a[i] = a[tmp];
            a[tmp] = tmp;
        }
    }

    return false;
}

int main()
{
    int a[] = { 2, 3, 1, 0, 2, 5, 3 };
    int len = sizeof(a) / sizeof(int);

    int dup;
    if (duplication_in_array(a, len, &dup)) {
        printf("%d\n", dup);
    }

    return 0;
}