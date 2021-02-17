
#include <chrono>
#include <iostream>

int main()
{
    std::chrono::hours hs{10};
    std::cout << "10 hours duration has " << hs.count() << std::endl;

    std::chrono::minutes mi{20};
    std::cout << "20 minutes duration has " << mi.count() << std::endl;
    
    std::chrono::milliseconds ms{3};                // 3 毫秒
    // 6000 microseconds consturcted from 3 milliseconds
    std::chrono::microseconds us = 2 * ms;
    // 30HZ clock using fractional ticks
    
    std::cout << "3 ms duration has " << ms.count() << " ticks" << std::endl;
    std::cout << "6000 us duration has " << us.count() << " ticks" << std::endl;
    
    return 0;
}