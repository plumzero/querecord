
#include <chrono>
#include <iostream>

int main()
{
    // 新纪元20秒后的 timepoint
    {
        std::chrono::steady_clock::time_point tp1 { std::chrono::duration<int>(20) };   // Epoch + 20 seconds;
        
        auto elapsed = tp1.time_since_epoch();
        std::cout << "elapsed = " << elapsed.count() << std::endl;
        
        auto ticks_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
        std::cout << "duration_cast: elapsed = " << ticks_ns << std::endl;
    }
    
    // 新纪元至现在的 timepoint
    {
        auto now = std::chrono::system_clock::now().time_since_epoch().count();
        auto now_s = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        
        std::cout << "now = " << now << std::endl;
        std::cout << "now_s = " << now_s << std::endl;
    }
    
    return 0;
}