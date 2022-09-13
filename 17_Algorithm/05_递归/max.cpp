
// 问题: 求 n 个元素中的最大者

// 分析: 将 n 个元素放到一个数组里，将 a[n-1] 与 max(a[0...n-2]) 比较取最大值，而后者是 a[n-2] 与 max(a[0...n-3]) 中的最大值
//  递归结束条件为数组中只有一个元素，此时最大值就是本身 a[0]


#include <stdio.h>

int max(int a[], int n)
{
    if (n == 1)
        return a[0];
    
    return max(a, n - 1) > a[n-1] ? max(a, n - 1) : a[n-1];
}

int main()
{
    int a[] = { 55, 33, 22, 77, 99, 88, 11, 44 };
    int len = sizeof(a) / sizeof(int);

    printf("%d\n", max(a, len));

    return 0;
}