
#include <stdio.h>
#include <math.h>

int main()
{
    int b = pow(2, 6) - 1;
    
    int a = 12345;
    
    int c = a % (b + 1);
    
    int d = a & b;
    
    printf("c=%d, d=%d\n", c, d);   // c=57, d=57
    
    return 0;
}