
// 问题: 已知有 n 个元素的无序序列，求该无序序列中的最大和次大元素。

// 分析:
// 1. 当只有一个元素时，只有最大元素，没有次大元素(这里可以将次大元素设定为某个数)
// 2. 当只有两个元素时，将其中的较大者作为最大元素，较小者作为次大元素
// 3. 当有多个元素时，以某个元素作为枢轴，将元素分成两部分，左侧部分不大于枢轴元素，右侧部分不小于枢轴元素。
//    分别找出左右两侧集合中的最大元素和次大元素，进行比较得到整体的最大元素和次大元素

// 采用枢轴的办法时，需要交换元素。但这是没有必要的，可以换成折半查找办法。

#include <stdio.h>
#include <limits.h>
#include <algorithm>

#define LESS_GREATER INT_MIN

int partition(int a[], int low, int high)
{
    int pivot = a[low];
    while (low < high) {
        while (low < high && a[high] >= pivot)
            high--;
        a[low] = a[high];
        while (low < high && a[low] <= pivot)
            low++;
        a[high] = a[low];
    }
    a[low] = pivot;

    return low;
}

void first_two_great(int a[], int low, int high, int* max1, int* max2)
{
    if (low == high) {
        *max1 = a[low];
        *max2 = LESS_GREATER;
    } else if (high - low == 1) {
        *max1 = std::max(a[low], a[high]);
        *max2 = std::min(a[low], a[high]);
    } else if (low < high) {    // 还得注意避免数组越界的风险
        int left_max1, left_max2, right_max1, right_max2;
        int index = partition(a, low, high);
        first_two_great(a, low, index, &left_max1, &left_max2);
        first_two_great(a, index + 1, high, &right_max1, &right_max2);
        *max1 = std::max(left_max1, right_max1);
        *max2 = std::max(std::min(left_max1, right_max1), std::max(left_max2, right_max2));
    }
}

void first_two_great2(int a[], int low, int high, int* max1, int* max2)
{
    if (low == high) {
        *max1 = a[low];
        *max2 = LESS_GREATER;
    } else if (high - low == 1) {
        *max1 = std::max(a[low], a[high]);
        *max2 = std::min(a[low], a[high]);
    } else {
        int left_max1, left_max2, right_max1, right_max2;
        int index = (low + high) / 2;
        first_two_great2(a, low, index, &left_max1, &left_max2);
        first_two_great2(a, index + 1, high, &right_max1, &right_max2);
        *max1 = std::max(left_max1, right_max1);
        *max2 = std::max(std::min(left_max1, right_max1), std::max(left_max2, right_max2));
    }
}


int main()
{
    {
        int a[] = { 21, 19, 29, 36, 78, 95, 55, 66, 80, 12 };
        int len = sizeof(a) / sizeof(int);

        int max1, max2;
        first_two_great(a, 0, len - 1, &max1, &max2);

        printf("%d %d\n", max1, max2);
    }

    {
        int a[] = { 21, 19, 29, 36, 78, 95, 55, 66, 80, 12 };
        int len = sizeof(a) / sizeof(int);

        int max1, max2;
        first_two_great2(a, 0, len - 1, &max1, &max2);

        printf("%d %d\n", max1, max2);
    }

    return 0;
}