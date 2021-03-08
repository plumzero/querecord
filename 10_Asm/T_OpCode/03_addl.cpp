
#include <iostream>

int main()
{
    int res;
    
    __asm__("movl $50, %%eax;"
            "movl $20, %%ebx;"
            "addl %%ebx, %%eax":"=a"(res));
            
    std::cout << res << std::endl;
    
    return 0;
}