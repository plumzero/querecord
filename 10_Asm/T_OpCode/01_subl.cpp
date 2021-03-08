
#include <iostream>

int main()
{
    int res;
    
    __asm__("movl $20, %%eax;"
            "movl $10, %%ebx;"
            "subl %%ebx, %%eax":"=a"(res));
            
    std::cout << res << std::endl;
    
    return 0;
}