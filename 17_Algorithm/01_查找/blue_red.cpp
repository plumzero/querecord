
#include <stdio.h>

/**
 * a: 待查找数组
 * len: 待查找数组长度
 * val: 待查找值
 * 
 * 返回值: 为了直观清晰，这里返回待查找元素下标
 */

// 找到数组中第一个出现的 val
int find_first_of(int a[], int len, int val)
{
    int left = -1, right = len;
    while (left + 1 != right) {
        int mid = left + (right - left) / 2;
        if (a[mid] < val)   // 蓝色区域是 < val 的值，红色区域是 >= val 的值
            left = mid;
        else
            right = mid;
    }

    // printf("left=%d,right=%d\n", left, right);  // debug 打印
    // 还要考虑到找不到的情况
    if (right >= len || a[right] != val) {
        return -1;
    }

    return right;
}

// 找到数组中最后一个小于 val 的数
int find_last_not_of(int a[], int len, int val)
{
    int left = -1, right = len;
    while (left + 1 != right) {
        int mid = left + (right - left) / 2;
        if (a[mid] < val)
            left = mid;
        else
            right = mid;
    }

    // printf("left=%d,right=%d\n", left, right);  // debug 打印
    // 还要考虑到找不到的情况
    if (right >= len || a[left] >= val) {
        return -1;
    }

    return left;
}
// find_first_of 和 find_last_not_of 的蓝红边界区域是相同的，不同的时前者返回 right，后者返回 left

// 找到数组中最后一个出现的 val
int find_last_of(int a[], int len, int val)
{
    int left = -1, right = len;
    while (left + 1 != right) {
        int mid = left + (right - left) / 2;
        if (a[mid] <= val)  // 蓝色区域是 <= val 的值，红色区域是 > val 的值
            left = mid;
        else
            right = mid;
    }

    // printf("left=%d,right=%d\n", left, right);  // debug 打印
    if (right >= len || a[left] != val) {
        return -1;
    }

    return left;
}

int main()
{
    {
        printf("find_first_of 测试:\n");
        //          0  1  2  3  4  5  6  7  8  9  x
        int a[] = { 1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9 };
        int len = sizeof(a) / sizeof(int);
        int val;

        val = 5;
        printf("find_first_of %d: %d\n", val, find_first_of(a, len, val));
        val = 7;
        printf("find_first_of %d: %d\n", val, find_first_of(a, len, val));
        val = -1;
        printf("find_first_of %d: %d\n", val, find_first_of(a, len, val));
        val = 10;
        printf("find_first_of %d: %d\n", val, find_first_of(a, len, val));
    }

    {
        printf("find_last_not_of 测试:\n");
        //          0  1  2  3  4  5  6  7  8  9  x
        int a[] = { 1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9 };
        int len = sizeof(a) / sizeof(int);
        int val;

        val = 5;
        printf("find_last_not_of %d: %d\n", val, find_last_not_of(a, len, val));
        val = 7;
        printf("find_last_not_of %d: %d\n", val, find_last_not_of(a, len, val));
        val = -1;
        printf("find_last_not_of %d: %d\n", val, find_last_not_of(a, len, val));
        val = 10;
        printf("find_last_not_of %d: %d\n", val, find_last_not_of(a, len, val));
    }

    {
        printf("find_last_of 测试:\n");
        //          0  1  2  3  4  5  6  7  8  9  x
        int a[] = { 1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9 };
        int len = sizeof(a) / sizeof(int);
        int val;

        val = 5;
        printf("find_last_of %d: %d\n", val, find_last_of(a, len, val));
        val = 7;
        printf("find_last_of %d: %d\n", val, find_last_of(a, len, val));
        val = -1;
        printf("find_last_of %d: %d\n", val, find_last_of(a, len, val));
        val = 10;
        printf("find_last_of %d: %d\n", val, find_last_of(a, len, val));
    }

    return 0;
}