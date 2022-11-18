
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