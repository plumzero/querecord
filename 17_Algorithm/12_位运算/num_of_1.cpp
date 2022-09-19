
// 15 二进制中 1 的个数

// 问题:
// 输入一个整数，输出该数二进制表示中 1 的个数。
// 例如，把 9 表示成二进制是 1001, 有 2 位是 1，因此输出结果是 2

// 分析:
// 略

#include <stdio.h>

// 是技巧吗? 默识
int func(int n)
{
    int count = 0;

    while (n != 0) {
        count++;
        n = (n - 1) & n;
    }

    return count;
}

// 尝试用下递归
int func2(int n)
{
    if (n == 0)
        return 0;
    
    return 1 + func2((n - 1) & n);
}

int main()
{
    printf("%d\n", func(9));
    printf("%d\n", func(0x7FFFFFFF));
    printf("%d\n", func(0xFFFFFFFF));
    printf("%d\n", func(0x80000000));
    
    printf("%d\n", func2(9));
    printf("%d\n", func2(0x7FFFFFFF));
    printf("%d\n", func2(0xFFFFFFFF));
    printf("%d\n", func2(0x80000000));

    return 0;
}