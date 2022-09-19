
// 问题:
// 考虑 n 位二进制数，有多少个数中不存在两个相邻的 1

// 分析:
// n 位二进制数中符合条件的个数符合 fibonacci 数列。
// 假设 n 为二进制数符合条件的数有 f(n) 个。当第 n 位为 0 时，则有 f(n-1) 个，当第 n 位为 1 时，则有 f(n-2) 个，
// 三者的关系是 f(n) = f(n-2) + f(n-1)

#include <stdio.h>

int func(int n) {

    if (n == 1) return 2;   // 0 1
    if (n == 2) return 3;   // 00 01 10

    return func(n - 2) + func(n - 1);
}

int main()
{
    printf("%d\n", func(3));
    printf("%d\n", func(7));

    return 0;
}