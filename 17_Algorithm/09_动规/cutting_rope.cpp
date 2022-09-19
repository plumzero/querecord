
// 14 剪绳子

// 问题:
// 一根长为 n 的绳子，把绳子剪为 m 段(m,n 都是整数，n>1并且m>1)，每段绳子的长度为记为 k[0],...,k[m]
// 问 k[0] × k[1] × ... × k[m] 可能的最大乘积是多少?
// 例如，当绳子的长度是 8 时，剪成长度为 2, 3, 3 的三段，此时得到的最大乘积为 18

// 分析:
// 对于一根绳子，至少要剪成 2 段，每段长度至少为 1 。
// 当 n = 1 时，乘积为 0; 当 n = 2 时，乘积为 1; 当 n = 3 时，乘积为 2 。
// 对于长度大于 3 的绳子，在剪第一刀后，假设两段长度为 i, n-i, 那么组合的最大值为 f(n) = max(f(i) x f(n-i))
// 而 f(i) 和 f(n-i) 之前已经计算过并保存，这样只需要将它们乘积，并比较出最大值即可

#include <stdio.h>

int max_products(int n)
{
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n == 3) return 2;

    int* products = new int[n + 1];

    products[0] = 0;
    products[1] = 1;
    products[2] = 2;
    products[3] = 3;

    // 先依次把子问题的解计算出来
    for (int i = 4; i <= n; i++) {
        int max = 0;
        // 剪第一刀时，可能的长度为 1, 2, 3, ..., n-1
        for (int j = 1; j <= i - 1; j++) {  // 根据对称性，可以将判断条件改为 j <= i / 2
            int prod = products[j] * products[i-j];
            if (prod > max) {
                max = prod;
            }
        }
        products[i] = max;
    }

    int res = products[n];
    delete products;

    return res;
}

int main()
{
    printf("cut(%d)=%d\n", 4, max_products(4));
    printf("cut(%d)=%d\n", 5, max_products(5));
    printf("cut(%d)=%d\n", 6, max_products(6));
    printf("cut(%d)=%d\n", 7, max_products(7));
    printf("cut(%d)=%d\n", 8, max_products(8));
    printf("cut(%d)=%d\n", 9, max_products(9));
    printf("cut(%d)=%d\n", 10, max_products(10));
    printf("cut(%d)=%d\n", 50, max_products(50));

    return 0;
}