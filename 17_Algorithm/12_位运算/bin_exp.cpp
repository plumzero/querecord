
// 计算整数 a 的 n 次幂

#include <stdio.h>

int bin_exp(int a, int n)
{
    int r = 1;
    
    while (n) {
        if (n & 0x1) {
            r = r * a;
        }
        a = a * a;
        n >>= 1;
    }

    return r;
}

int main()
{
    printf("2^5 = %d\n", bin_exp(2, 5));
    printf("3^1 = %d\n", bin_exp(3, 1));
    printf("4^6 = %d\n", bin_exp(4, 6));

    return 0;
}