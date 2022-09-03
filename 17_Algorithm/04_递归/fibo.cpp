
// 体会递归化分治

#include <stdio.h>

// 递归
int fibo1(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    
    return fibo1(n - 1) + fibo1(n - 2);
}

// 尝试化成循环
// 初始条件为 n, 迭代条件为 n != 0 且 n != 1, 迭代因子为 n 自减

// 好像卡住了，化成循环的方法并非那么千篇一律

// 怎么办呢？以 f(5) 为例 f(5) = f(4) + f(3), 而 f(4) = f(3) + f(2) ，f(3) 计算了两次，应该采用分治的方法，拆分成子问题
// 将子问题的解保存起来，又像是动态规则
int fibo2(const int n)
{
    int a[n + 1] = { 0 }; // 存储解
    a[0] = 0;
    a[1] = 1;

    for (int i = 2; i <= n; i++) {
        a[i] = a[i - 1] + a[i - 2];
    }

    return a[n];
}

// 当然，也可以不保存中间结果
int fibo3(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}

int main()
{
    printf("fibo1(10)=%d\n", fibo1(10));
    printf("fibo2(10)=%d\n", fibo2(10));
    printf("fibo3(10)=%d\n", fibo3(10));

    return 0;
}