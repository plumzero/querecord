
// 最大公约数

#include <stdio.h>

int gcd(int a, int b)
{
    if (a < b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    int r;
    do {
        r = a % b;
        a = b;
        b = r;
    } while(r != 0);

    return r;
}

int main()
{
    printf("%d\n", gcd(285,220));

    return 0;
}