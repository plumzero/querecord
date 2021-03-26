
#include <chrono>
#include <iostream>

int main()
{   
    std::cout << std::boolalpha << std::chrono::system_clock::is_steady << std::endl;
    std::cout << std::boolalpha << std::chrono::steady_clock::is_steady << std::endl;
    std::cout << std::boolalpha << std::chrono::high_resolution_clock::is_steady << std::endl;
    
    return 0;
}