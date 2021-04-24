
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    
    for (size_t i = 0; i < 8; i++) {
        std::cout << rd() << " ";
    }
    std::cout << std::endl;

    return 0;
}