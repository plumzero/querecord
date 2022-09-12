
// 问题: 给定两个正整数，求最大公约数与最小公倍数

#include <stdio.h>

void common_values(int m, int n)
{
    if (m < n) {    // 保证 m 较大
        int t = m;
        m = n;
        n = t;
    }

    int _m = m;
    int _n = n;

    int r;
    do {
        r = m % n;
        m = n;
        n = r;
    } while (r != 0);

    printf("%d 和 %d 的最大公约数为 %d, 最小公倍数为 %d\n", _m, _n, m, _m * _n / m);
}

int main()
{
    common_values(51, 34);

    return 0;
}