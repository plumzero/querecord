
#include <chrono>
#include <iostream>

int main()
{
    {
        auto now = std::chrono::steady_clock::now().time_since_epoch().count();
        auto now_s = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        
        std::cout << "now = " << now << std::endl;
        std::cout << "now_s = " << now_s << std::endl;
    }
    
    {
        auto instant = std::chrono::system_clock::now();
        
        std::time_t the_time = std::chrono::system_clock::to_time_t(instant);
        
        auto now = std::chrono::system_clock::from_time_t(the_time);
        
        std::cout << "instant = " << instant.time_since_epoch().count() << std::endl;
        std::cout << "now = " << now.time_since_epoch().count() << std::endl;
    }
    
    return 0;
}