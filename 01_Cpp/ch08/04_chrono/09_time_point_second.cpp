
#include <chrono>
#include <iostream>
#include <sys/time.h>

inline time_t get_ticks()
{    
    return std::chrono::system_clock::now().time_since_epoch().count() * 
            std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
}

// 与 gettimeofday 获取秒数相同功能的函数
int main()
{
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        std::cout << "tv.sec = " << tv.tv_sec << std::endl;
    }

    {
        std::chrono::system_clock::time_point instant = std::chrono::system_clock::now();
        std::time_t ticks = instant.time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
        std::cout << "now = " << ticks << std::endl;

        std::cout << "std::chrono::system_clock::period::num = " << std::chrono::system_clock::period::num << std::endl;
        std::cout << "std::chrono::system_clock::period::den = " << std::chrono::system_clock::period::den << std::endl;  
    }

    {
        std::cout << "now = " << get_ticks() << std::endl;
    }
    
    return 0;
}