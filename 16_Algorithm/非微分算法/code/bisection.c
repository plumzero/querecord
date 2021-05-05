
#include <stdio.h>
#include <math.h>

#define EPS     1.0e-6


typedef double (*fun)(double);

double bisection(fun f, double a, double b)
{
    double c, fa, fb, fc;

    while (fabs(a - b) > EPS) {
        c = (a + b) / 2.0;
        fa = (*f)(a);
        fb = (*f)(b);
        fc  = (*f)(c);
        
        if (fa * fc < 0)
            b = c;
        else
            a = c;
    }
    
    return c;
}

double myfunc(double x)
{
    return x * x - 13;
}

int main ()
{
    double p = bisection(myfunc, 0.4, 70.0);
    
    printf("p=%f\n", p);
    
    return 0;
}