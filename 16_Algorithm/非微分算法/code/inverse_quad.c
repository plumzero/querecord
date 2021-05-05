
#include <stdio.h>
#include <math.h>

#define EPS     1.0e-6


typedef double (*fun)(double);

double inverse_quad(fun f, double a, double b)
{
    double c, d, fa, fb, fc, fd;
    while (fabs(a - b) > EPS) {
        c = (a + b) / 2;
        fa = (*f)(a);
        fb = (*f)(b);
        fc = (*f)(c);
        
        if (fa != fc && fb != fc) {
            d = fa * fb * c / ((fa - fc) * (fb - fc)) + 
                fa * fc * b / ((fa - fb) * (fc - fb)) + 
                fb * fc * a / ((fb - fa) * (fc - fa));
        } else {
            d = fa * b / (fa - fb) + fb * a / (fb - fa);
        }
        
        fd = (*f)(d);
        b = d;
        if (fd * fc < 0)
            a = c;
        else if (fd * fb < 0)
            a = b;
    }
    
    return d;
}

double myfunc(double x)
{
    return x * x - 13;
}

int main()
{
    double x = inverse_quad(myfunc, 0.4, 70.0);
    
    printf("%f\n", x);

    return 0;
}