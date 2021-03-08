
#include <iostream>

int main()
{   
    int dec;
    int hex;
    
    asm("movl $20, %%eax;":"a="(dec));
    asm("movl $0x20, %%ebx;":"b="(hex));
            
    std::cout << "dec=" << dec << std::endl;
    std::cout << "hex=" << hex << std::endl;
    
    return 0;
}