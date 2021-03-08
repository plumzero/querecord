
#include <iostream>

int main()
{
    int res;
    
    __asm__("movl $5, %%eax;":"a="(res));
    
    std::cout << res << std::endl;
    
    return 0;
}