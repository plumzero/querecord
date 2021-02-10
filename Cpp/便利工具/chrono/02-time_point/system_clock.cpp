
#include <iostream>
#include <chrono>

int main()
{
    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::cout << "Hello World" << std::endl;
    std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
    std::cout << (t2 - t1).count() << " tick count" << std::endl;
    
    return 0;
}