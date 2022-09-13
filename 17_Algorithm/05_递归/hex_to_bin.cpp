
// 问题: 十进制整数转换为二进制整数

// 结束条件: n 为 0

#include <stdio.h>

void hex_to_bin(int n)
{
    if (n == 0)
        return ;
    
    hex_to_bin(n >> 1);
    
    printf("%d", n % 2);
}

int main()
{
    hex_to_bin(136);

    return 0;
}