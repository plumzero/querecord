
// 问题:
// 输入两个整数 m 和 n, 计算需要改变 m 的二进制表示中的多少位才能得到 n。
// 例如 10 的二进制表示为 1010, 13 的二进制表示为 1101,则需要改变 1010 中的 3 位才能得到 1101

// 分析:
// 求这两个数的异或，之后统计异或结果中 1 的数量

int func(int m, int n)
{
    int r = m ^ n;

    int count = 0;

    while (r != 0) {
        count++;
        r = (r - 1) & r;
    }

    return count;
}

#include <stdio.h>

int main()
{
    printf("%d\n", func(10, 13));

    return 0;
}