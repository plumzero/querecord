
#include <stdio.h>
#include <math.h>

#define PHI     (-1 + sqrt(5)) / 2.0

#define CRIT   1.e-8


typedef double (*fun)(double);

double gss(fun f, double x0, double x2, double x1)
{
    double x3;
    
    if (fabs(x0 - x1) < CRIT)
        return (x0 + x1) / 2.0;
    
    x3 = x0 + (x2 - x0) / PHI;
    if ((*f)(x3) < (*f)(x2))
        return gss(f, x0, x3, x2);    // 在 x2 x3 x1 构成的区间内搜寻
    
    return gss(f, x1, x2, x3);        // 在 x3 x2 x0 构成的区间内搜寻
}

double ff(double x)
{
    return (x * x - 13) * (x * x - 13);
}

int main()
{
    double x0 = 0, x1 = 30;             // 变量初始区间
    double x2 = x0 + (x1 - x0) * PHI;   // 黄金分割点
    
    double x = gss(ff, x0, x2, x1);
    
    printf("%f\n", x);
    
    return 0;
}