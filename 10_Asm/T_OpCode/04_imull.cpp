
#include <cstdio>

int main()
{
    int val1, val2, add, sub, mul;
    
    val1 = 100;
    val2 = 20;
    
    asm("addl %%ebx, %%eax;":"=a"(add):"a"(val1), "b"(val2));
    asm("subl %%ebx, %%eax;":"=a"(sub):"a"(val1), "b"(val2));
    asm("imull %%ebx, %%eax;":"=a"(mul):"a"(val1), "b"(val2));
    
    printf("%d + %d = %d\n", val1, val2, add);
    printf("%d - %d = %d\n", val1, val2, sub);
    printf("%d * %d = %d\n", val1, val2, mul);
    
    return 0;
}