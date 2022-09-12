
// 问题: 输入一个十进制整数，将其转换为二进制整数

#include <stdio.h>

void hex_to_bin(int n)
{
    int buf[16] = { 0 };
    int len = 0;
    while (n != 0) {
        buf[len++] = n % 2;
        n = n >> 1;
    }

    // 打印
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", buf[i]);
    }
    printf("\n");
}

int main()
{
    hex_to_bin(278);
    hex_to_bin(279);

    return 0;
}