
#include <stdio.h>

typedef double (*fun)(double);

double fibo(fun f, double x0, double x1, int n)
{
    double fibn[100], r, x2, x3;
    int k;
    
    fibn[0] = 0;
    fibn[1] = 1;
    
    for (k = 2; k <= n; k++)
        fibn[k] = fibn[k-1] + fibn[k-2];    // 计算 Fibonacci 级数
    
    x2 = x0 + (x1 - x0) * fibn[n-1] / fibn[n];
    
    for (k = 1; k < n - 2; k++) {
        x3 = x0 + (x2 - x0) * fibn[n - k - 1] / fibn[n - k];
        if ((*f)(x3) < (*f)(x2)) {
            x1 = x2;
            x2 = x3;
        } else {
            x0 = x1;
            x1 = x3;
        }
    }
    
    return x3;
}

double ff(double x)
{
    return (x * x - 13) * (x * x - 13);
}

int main()
{
    int n = 50;
    
    double x0 = 0, x1 = 30;
    
    double x = fibo(ff, x0, x1, n);
    
    printf("%f\n", x);
    
    return 0;
}