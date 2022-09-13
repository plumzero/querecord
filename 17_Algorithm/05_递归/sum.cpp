
#include <stdio.h>

int sum(int a[], int n)
{
    if (n == 1)
        return a[0];
    
    return a[n-1] + sum(a, n - 1);
}

int main()
{
    int a[] = { 5, 4, 3, 2, 1, 6, 7, 8, 9 };
    int len = sizeof(a) / sizeof(int);

    printf("%d\n", sum(a, len));

    return 0;
}