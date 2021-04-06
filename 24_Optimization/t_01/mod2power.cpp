
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "common.hpp"

/**
   其中一次执行结果:
        % timecost = 3446
        & timecost = 2261
 */
int main()
{
    {
        int op1 = 1234567890;
        int op2 = pow(2, 10) - 1;
        int TOTAL = 1000000;
        
        auto b = std::chrono::steady_clock::now();
        for (int i = 0; i < TOTAL; i++) {
            int res = op1 % (op2 + 1);
            // printf("res=%d\n", res);
            (void) res;
        }
        auto e = std::chrono::steady_clock::now();
        printf("%% timecost = %ld\n", timediff<std::chrono::microseconds>(b, e));

        b = std::chrono::steady_clock::now();
        for (int i = 0; i < TOTAL; i++) {
            int res = op1 & op2;
            // printf("res=%d\n", res);
            (void) res;
        }
        e = std::chrono::steady_clock::now();
        printf("& timecost = %ld\n", timediff<std::chrono::microseconds>(b, e));
    }
    
    return 0;
}