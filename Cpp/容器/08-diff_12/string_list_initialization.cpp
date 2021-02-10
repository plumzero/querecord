
#include <stdio.h>
#include <string>

int main()
{
    std::string str{ '\x01', '\x00', '\x25', '\xaf', '\x34' };

    for (const auto & ele : str) {
        printf("%02X ", static_cast<int>((unsigned char)ele));
    }
    printf("\n");
    
    return 0;
}
