
#include <stdio.h>
#include <math.h>

#define EPS     1.0e-6


typedef double (*fun)(double);

double regula_falsi(fun f, double a, double b)
{
    double c, fa, fb, fc, fmin;

    do {
        fa = (*f)(a);
        fb = (*f)(b);
        c = b - (b - a) * fb / (fb - fa);
        fc = (*f)(c);
        
        if (fa * fc < 0)
            b = c;
        else
            a = c;
        
        fmin = fabs(fa);
        if (fmin > fabs(fb)) fmin = fabs(fb);
    } while (fabs(fabs(fc) - fmin) > EPS);
    
    return c;
}

double myfunc(double x)
{
    return x * x - 13;
}

int main ()
{
    double p = regula_falsi(myfunc, 0.4, 70.0);
    
    printf("p=%f\n", p);
    
    return 0;
}