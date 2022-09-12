
// 问题: 给定一个整数，对其进行质因数分解

#include <stdio.h>

void prime_factor(int n)
{
    int x = 2;  // 从最小的质数开始
    while (n != 1) {
        while (n % x == 0) {
            n /= x;
            printf("%d ", x);
        }
        x++;
    }
    printf("\n");
}

int main()
{
    prime_factor(54);
    prime_factor(270);

    return 0;
}