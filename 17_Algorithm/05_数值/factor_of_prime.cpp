
// 分解质因数

// 试求解 60 的质因数

// 先计算得到关于 60 的一半，也就是 1 ~ 30 之间的质因数数组

#include <stdio.h>

// 这里不考虑异常输入
// 数组 a 中的元素应保证全部为 0，且 val <= len
void eval_prime(int val, int a[], int len)
{
    for (int i = 2; i <= val; i++) {
        if (a[i] == 0) {
            for (int j = 2 * i; j <= val; j += i) {
                a[j] = 1;
            }
        }
    }
    int index = 0;
    for (int i = 2; i < len && i < val; i++) {
        if (a[i] == 0)
            a[index++] = i;
        else
            a[i] = 0;   // 也置为 0, 以便后续计算
    }
}

int main()
{
    int x = 60;

    int a[30] = { 0 };

    eval_prime(x / 2, a, 30);

    int len = -1;
    while (a[++len] != 0);

    // printf("len=%d\n", len);
    printf("分解的质因数有: ");
    int i = 0;
    while (x != 1) {
        if (i == len)
            break;
        while (x % a[i] == 0) {
            printf("%d ", a[i]);
            x = x / a[i];
        }
        i++;
    }
    printf("\n");

    return 0;
}