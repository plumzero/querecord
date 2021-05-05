
#include <stdio.h>

/**
 * 将一个数组 A 分拆成两个部分，使 A 中大于等于 0 的元素放在左边，小于 0 的元素放在右边。
 * 要求不占用额外的存储空间。
 */


int main()
{
    int a[] = { -7, 0, 5, -8, 9, -4, 3, -2 };
    
    int front, last;
    
    
    front = 0;
    last = sizeof(a) / sizeof(a[0]) - 1;

    while (front < last) {
        while (a[front] >= 0)
            front++;
        while (a[last] < 0)
            last--;
        
        if (front < last) {
            int t = a[front];
            a[front] = a[last];
            a[last] = t;
        }
    }
    
    int i;
    for (i = 0; i < sizeof(a)/sizeof(a[0]); i++)
        printf("%4d", a[i]);
    printf("\n");
    
    return 0;
}