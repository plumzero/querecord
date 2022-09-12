
// 角谷猜想
// 对于每一个正整数，如果它是奇数，则对它乘 3 再加 1，如果它是偶数，则对它除以2，如此循环，最终都能够得到1

// 问题: 输入一个正整数，求出角谷猜想过程中的每一个数。

#include <stdio.h>

void choku_guess(int n)
{
    printf("%d", n);
    while (n != 1) {
        switch (n & 1) {
            case 1: n = 3 * n + 1; break;
            case 0: n = n >> 1; break;
        }
        printf(" -> %d", n);
    }
    printf("\n");
}

int main()
{
    choku_guess(26);
    choku_guess(37);

    return 0;
}