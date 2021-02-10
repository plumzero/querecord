
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#define PI      3.1415926
#define NE      2.718281829
#define GR      1.618033988749

#define COUNT_FOR_TEST      10000000

/**
 * g++ -g -std=c++11 -Wall -W -Wno-unused-variable xx.cpp -o xx
 */

uint64_t microseconds()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    
    return tv.tv_sec * 10000000 + tv.tv_usec;
}
/**
 * 结论:
 *  float 进行多次乘/除运算后，准确性有很大偏差，不再可信。
 *  double 进行多次乘/除运算后，依然可以保证有可信的精确度。
 *
 *  乘法: float 与 double 的效率不相伯仲。
 *  除法: 千万次运算，float 只比 double 快 10% 。
 *
 *  在 C/C++ 中进行浮点运算时，更建议使用 double 而不是 float 。
 */

int main()
{
    printf("\n===== 乘法结果单次对比测试 =====\n");
    {
        double d = PI * NE * GR;
        float f = PI * NE * GR;
        printf("d=%f\n", d);
        printf("f=%f\n", f);
    }
    
    printf("\n===== 除法结果单次对比测试 =====\n");
    {
        double d = PI / NE / GR;
        float f = PI / NE / GR;
        printf("d=%f\n", d);
        printf("f=%f\n", f);
    }

    printf("\n===== 乘法效率测试 =====\n");
    {
        uint64_t b, e;
        
        size_t i;
        
        double td = 0.0f;
        
        b = microseconds();
        for (i = 0; i < COUNT_FOR_TEST; i++) {
            double d = PI * NE * GR;
            td += d;
        }
        e = microseconds();
        
        printf("double: totally test %d cost %lu microseconds(sum=%f)\n", COUNT_FOR_TEST, e - b, td);
        
        float tf = 0.0f;
        
        b = microseconds();
        for (i = 0; i < COUNT_FOR_TEST; i++) {
            float f = PI * NE * GR;
            tf += f;
        }
        e = microseconds();

        printf("float: totally test %d cost %lu microseconds(sum=%f)\n", COUNT_FOR_TEST, e - b, tf);
    }
    
    printf("\n===== 除法效率测试 =====\n");
    {
        uint64_t b, e;
        
        size_t i;
        
        double td = 0.0f;
        
        b = microseconds();
        for (i = 0; i < COUNT_FOR_TEST; i++) {
            long double d = PI / NE / GR;
            td += d;
        }
        e = microseconds();
        
        printf("double: totally test %d cost %lu microseconds(sum=%f)\n", COUNT_FOR_TEST, e - b, td);
        
        float tf = 0.0f;
        
        b = microseconds();
        for (i = 0; i < COUNT_FOR_TEST; i++) {
            float f = PI / NE / GR;
            tf += f;
        }
        e = microseconds();

        printf("float: totally test %d cost %lu microseconds(sum=%f)\n", COUNT_FOR_TEST, e - b, tf);
    }
    
    printf("\n===== test over =====\n");
    
    return 0;
}