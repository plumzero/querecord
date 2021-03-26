
#include <chrono>
#include <iostream>

int main()
{   
    using TimePoint1 = std::chrono::time_point<std::chrono::system_clock>;
    using TimePoint2 = std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes>;
    
    TimePoint1 tp1 { std::chrono::seconds(120) };
    TimePoint2 tp2 { std::chrono::minutes(2) };
    
    std::cout << "tp1 ticks: " << tp1.time_since_epoch().count()
              << "tp2 ticks: " << tp2.time_since_epoch().count() << std::endl;
              
    std::cout << "tp1 is " << ((tp1 == tp2) ? "equal" : "not equal") << " to tp2" << std::endl;
    
    return 0;
}