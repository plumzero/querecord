
#include <stdio.h>
#include <iostream>
#include <string>

static unsigned char ucs[32] = {
    0x20, 0x20, 0x20, 0x20, 0x2B, 0x20, 0xE6, 0x9C,
    0xAC, 0xE5, 0x9C, 0xB0, 0xE7, 0x94, 0x9F, 0xE6,
    0x88, 0x90, 0xE5, 0xAF, 0x86, 0xE9, 0x92, 0xA5,
    0xE5, 0xAF, 0xB9, 0x28, 0xE8, 0xA1, 0x8D, 0xE7
};

int main()
{
    {
        /** [1] 取容器的后 10 个元素 */
        std::cout << "取容器的后 10 个元素:" << std::endl; 
        std::string str(ucs + sizeof(ucs) - 10, ucs + sizeof(ucs));
        std::string::iterator it;
        
        for (it = str.begin(); it != str.end(); it++) {
            printf("0x%02X ", static_cast<int>((unsigned char)*it));
        }
        printf("\n");
    }

    {
        /** [2] 取容器的前 8 个元素 */
        std::cout << "取容器的前 8 个元素:" << std::endl; 
        std::string str(ucs, ucs + 8);
        std::string::iterator it;
        
        for (it = str.begin(); it != str.end(); it++) {
            printf("0x%02X ", static_cast<int>((unsigned char)*it));
        }
        printf("\n");
    }
    
    {
        /** [2] 按索引取容器的 [5, 12)的元素 */
        std::cout << "按索引取容器的 [5, 12)的元素:" << std::endl;
        std::string str(ucs + 5, ucs + 12);
        std::string::iterator it;
        for (it = str.begin(); it != str.end(); it++) {
            printf("0x%02X ", static_cast<int>((unsigned char)*it));
        }
        printf("\n");
    }
    
    return 0;
}