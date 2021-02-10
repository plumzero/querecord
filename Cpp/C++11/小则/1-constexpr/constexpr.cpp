
#include <cstdio>
#include <cstdint>
#include <string>
#include <sys/time.h>

#define COUNT_FOR_TEST 1000000

uint64_t now_time()
{
    struct timeval tv{0,0};
    
    gettimeofday(&tv, nullptr);
    
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int main()
{
    printf("整型计算对比测试:\n");
    {
        uint64_t b, e;
        b = now_time();
        
        uint64_t seconds_in_one_day = 60 * 60 * 24;
        
        size_t i, tmp;
        for (i = 1; i < COUNT_FOR_TEST; i++) {
            tmp = seconds_in_one_day * i;
        }
        
        e = now_time();
        
        printf("cost %lu microseconds\n", e - b);
    }   
    
    {
        uint64_t b, e;
        b = now_time();
        
        constexpr uint64_t seconds_in_one_day = 60 * 60 * 24;
        
        size_t i, tmp;
        for (i = 1; i < COUNT_FOR_TEST; i++) {
            tmp = seconds_in_one_day * i;
        }
        
        e = now_time();
        
        printf("cost %lu microseconds\n", e - b);
    }
    
    return 0;
}