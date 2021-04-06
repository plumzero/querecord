
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "common.hpp"

/**
   其中一次执行结果:
         x timecost = 2343
        << timecost = 1709
 */
int main()
{
    {
        int op = 123456;
        constexpr int TOTAL = 1000000;
        
        auto b = std::chrono::steady_clock::now();
        for (int i = 0; i < TOTAL; i++) {
            int res = op * 63;
            // printf("res=%d\n", res);
            (void) res;
        }
        auto e = std::chrono::steady_clock::now();
        printf(" x timecost = %ld\n", timediff<std::chrono::microseconds>(b, e));

        b = std::chrono::steady_clock::now();
        for (int i = 0; i < TOTAL; i++) {
            int res = (op << 6) - op;
            // printf("res=%d\n", res);
            (void) res;
        }
        e = std::chrono::steady_clock::now();
        printf("<< timecost = %ld\n", timediff<std::chrono::microseconds>(b, e));
    }
    
    return 0;
}