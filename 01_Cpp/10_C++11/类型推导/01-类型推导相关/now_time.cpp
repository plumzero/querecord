
#include <cstdint>
#include <iostream>
#include <sys/time.h>

auto now_time = []() -> uint64_t {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
};

int main()
{
    std::cout << now_time() << std::endl;
    
    return 0;
}