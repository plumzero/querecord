
#include <stdio.h>

// 有序二分定位代码片段

// 升序稳定定位
void locate_point_asc(int* a, int len, int point) {
    int low = 0, high = len - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (point >= a[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    printf("low=%d, high=%d, mid=%d\n", low, high, mid);
}

// 降序稳定定位
void locate_point_desc(int* a, int len, int point) {
    int low = 0, high = len - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (point > a[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    printf("low=%d, high=%d, mid=%d\n", low, high, mid);
}

int main()
{
    {
        int a[] = { 1, 1, 2, 3, 3, 4, 5, 6, 9 };
        locate_point_asc(a, sizeof(a)/sizeof(int), 3);
    }

    {
        int a[] = { 9, 6, 5, 4, 3, 3, 2, 1, 1 };
        locate_point_desc(a, sizeof(a)/sizeof(int), 3);   
    }

    return 0;
}