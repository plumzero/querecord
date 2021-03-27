
#include <chrono>
#include <iostream>

int main()
{   
    // 认识 duration<T,P>
    {
        // 1 秒 1000 次滴答，共 15 次滴答(15 毫秒)
        std::chrono::duration<int, std::milli> IBM650_divide{15};
        // 1 秒 1 次滴答，共 60 次滴答(1 分钟)
        std::chrono::duration<int> minute { 60 };
        // 60 秒 1 次滴答，共 60 次滴答(1 小时)
        std::chrono::duration<double, std::ratio<60>> hour { 60 };
        // 1 秒 1000000 次滴答，共 1000 次滴答(1 毫秒)
        std::chrono::duration<long, std::micro> millisecond { 1000L };
        // 1 秒 5 次滴答，共 5.5 次滴答(1.1 秒)
        std::chrono::duration<double, std::ratio<1,5>> tiny { 5.5 };
    }
    
    // 别名的使用
    {
        std::chrono::hours hs{ 10 };
        std::chrono::minutes mi{ 20 };
        std::chrono::milliseconds ms{ 3 };
        std::chrono::microseconds us { 4000 };
    }
    
    // count()
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
    }
    
    // 自运算
    {
        std::chrono::duration<double, std::ratio<1,5>> tiny { 5.5 };
        std::chrono::microseconds very_tiny { 100 };
        ++tiny;
        very_tiny--;
        
        std::cout << "tiny = " << tiny.count() << std::endl;
        std::cout << "very_tiny = " << very_tiny.count() << std::endl;
    }
    
    // 二元运算: 同类型
    {
        std::chrono::duration<double, std::ratio<1, 5>> tiny { 5.5 };
        std::chrono::duration<double, std::ratio<1, 5>> small { 7.5 };
        
        auto total = tiny + small;
        
        std::cout << "total = " << total.count() << std::endl;  // 13
    }

    // 二元运算: 不同类型
    {
        std::chrono::milliseconds ten_minutes { 600000 };
        std::chrono::minutes half_hour { 30 };
        
        auto total = ten_minutes + half_hour;
        
        std::cout << "total = " << total.count() << std::endl;  // 2400000 milliseconds = 40 minutes
    }
    
    // 二元运算: 不同类型
    {
        std::chrono::minutes ten_minutes { 10 };
        std::chrono::duration<double, std::ratio<1,5>> interval { 4500.0 };     // 15 minutes
        
        auto total = ten_minutes + interval;
        
        std::cout << "total = " << total.count() << std::endl;  // 7500 个滴答，每个滴答 1/5 秒
    }
    
    // 一元复合运算
    {
        std::chrono::minutes short_time { 20 };
        std::chrono::minutes shorter_time { 10 };
        short_time += shorter_time;
        
        std::chrono::hours long_time { 3 };
        short_time += long_time;
        
        std::cout << "short_time = " << short_time.count() << std::endl;
    }

    
    return 0;
}