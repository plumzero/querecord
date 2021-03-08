
#include <iostream>

int main()
{   
    char c;
    short s;
    int i;
    
    asm("movl $65, %%eax;":"c="(c));
    
    std::cout << "c=" << c << std::endl;
    
    return 0;
}