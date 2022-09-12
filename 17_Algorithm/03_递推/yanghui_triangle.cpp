
// 问题: 输出 n 阶杨辉三角

// 6 阶示例:
// 1
// 1 1
// 1 2 1
// 1 3 3 1
// 1 4 6 4 1
// 1 5 x x 5 1
// x 表示 10

// 分析:
//  1. 1 阶三角最底层有 1 个数，2 阶三角最底层有 2 个数，... 以此类推，n 阶三角最底层应该有 n 个数。
//  2. 对于某层，该层的数值等于上一层同列值与上一层同列值的前一个值的加和，即 a[i][j] = a[i-1][j-1] + a[i-1][j]

// 实现:
// 在一个矩阵中实现杨辉三角，同时为了计算方便，下标从 1 开始

#include <stdio.h>
#include <string.h>

void yanghui_triangle(const int n)
{
    int a[n + 1][n + 1] = { 0 };
    memset(a, 0, sizeof(a));
    a[0][1] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = a[i-1][j-1] + a[i-1][j];
        }
    }

    // 打印
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    yanghui_triangle(1);
    yanghui_triangle(2);
    yanghui_triangle(6);

    return 0;
}