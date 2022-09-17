
// 11 旋转数组的最小数字

// 问题:
// 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
// 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素
// 例如 { 3, 4, 5, 1, 2 } 是 { 1, 2, 3, 4, 5 } 的一个旋转，该数组
// 的最小值为 1

// 分析:
// 旋转后的数组是局部有序的，可以尝试使用二分查找。
// 将旋转数组分成两个部分，左和右。定义两个索引 left 和 right，分别
// 指向左边数组的首元素和右边数组的尾元素。计算左右索引的中间索引 mid，
// 若中间元素大于左索引元素，则最小值在 [mid, right] 中，若中间元素小
// 于右索引元素，则最小值在 [left, mid] 中，如此往复，直到 left 指向
// 左数组的尾元素，right 指向右数组的首元素，此时 right - left == 1

// 对于特殊的旋转数组，比如 { 1, 0, 1, 1, 1 } 和 { 1, 1, 1, 0, 1 }
// 都可以看作是递增数组 { 0, 1, 1, 1, 1 } 的旋转，这个时候二分查找不
// 再有效，应该采用顺序查找

#include <stdio.h>

int min_order(int a[], int start, int end)
{
    int min = a[start];
    for (int i = start + 1; i <= end; i++) {
        if (min > a[i]) {
            min = a[i];
        }
    }

    return min;
}

int get_min(int a[], int len)
{
    // assert(a != nullptr && len > 0);

    int left = 0;
    int right = len - 1;
    int mid;
    while (left < right) {
        if (right - left == 1) {
            mid = right;
            break;
        }
        mid = left + (right - left) / 2;
        if (a[mid] == a[left] && a[mid] == a[right])
            return min_order(a, left, right);

        if (a[mid] >= a[left]) {
            left = mid;
        } else if (a[mid] <= a[right]) {
            right = mid;
        }
    }

    return a[mid];
}

int main()
{
    {
        int a[] = { 3, 4, 5, 1, 2 };
        int len = sizeof(a) / sizeof(int);

        printf("%d\n", get_min(a, len));
    }

    {
        int a[] = { 1, 0, 1, 1, 1 };
        int len = sizeof(a) / sizeof(int);

        printf("%d\n", get_min(a, len));
    }

    return 0;
}

