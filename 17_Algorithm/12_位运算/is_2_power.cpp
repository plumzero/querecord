
// 判断一个数是否是 2 的幂次方结果

#include <stdio.h>

bool is_2_power(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

int main()
{
    printf("0: %d\n", is_2_power(0));
    printf("1: %d\n", is_2_power(1));
    printf("2: %d\n", is_2_power(2));
    printf("3: %d\n", is_2_power(3));
    printf("7: %d\n", is_2_power(7));
    printf("1024: %d\n", is_2_power(1024));

    return 0;
}