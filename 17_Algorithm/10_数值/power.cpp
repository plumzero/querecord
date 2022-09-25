
// 16 数值的整数次方

// 问题:
// 实现函数 double power(double base, int exponent), 求 base 的 exponent 次方。
// 说明: 不得使用库函数，同时不需要考虑大数问题

// 分析:
// 在实现时需要考虑一些特殊的情况，如下:
// 1. 幂值为 0
// 2. 幂值为负值时，基数为 0
// 由于返回值是计算结果，在出现参数传入异常时，程序应该有所表示。这里设置一个全局异常标识
// 另外还要注意，对于两个浮点类型之间是否相等的比较方法

#include <stdio.h>

bool equal(double l, double r)
{
    if (l - r < 0.0000001 && l - r > -0.0000001)
        return true;

    return false;
}

bool _error_flag;

double power(double base, int exponent)
{
    _error_flag = false;

    if (exponent == 0) return 1.0;
    if (equal(base, 0.0) && exponent < 0) {
        _error_flag = true;
        return 0.0;
    }

    int abs_exponent = exponent;
    if (exponent < 0) {
        abs_exponent = -exponent;
    }

    double result = 1.0;
    for (int i = 1; i <= abs_exponent; i++) {
        result *= base;
    }

    if (exponent < 0) {
        result = 1 / result;
    }

    return result;
}

// 分析二:
// 在正式计算那一块，可以不用计算 abs(exponent) 的次数。
// 比如 exponent 为 8 时，可以计算两个 exponet 为 4 的乘积，而后者又是两个 expoent 为 2 的乘积
// 可以尝试一下递归

double _power2(double base, int abs_exponent)
{
    if (abs_exponent == 1) {
        return base;
    }

    double result = _power2(base, abs_exponent >> 1);
    result *= result;
    
    if (abs_exponent & 1) {
        result *= base;
    }

    return result;
}

double power2(double base, int exponent)
{
    _error_flag = false;

    if (exponent == 0) return 1.0;
    if (equal(base, 0.0) && exponent < 0) {
        _error_flag = true;
        return 0.0;
    }

    int abs_exponent = exponent;
    if (exponent < 0) {
        abs_exponent = -exponent;
    }

    double result = _power2(base, abs_exponent);

    if (exponent < 0) {
        result = 1 / result;
    }

    return result;
}

int main()
{
    printf("%f %d\n", power(2, 3), _error_flag);
    printf("%f %d\n", power(-2, 3), _error_flag);
    printf("%f %d\n", power(2, -3), _error_flag);
    printf("%f %d\n", power(2, 0), _error_flag);
    printf("%f %d\n", power(0, 0), _error_flag);
    printf("%f %d\n", power(0, 4), _error_flag);
    printf("%f %d\n", power(0, -4), _error_flag);   // 这里有个问题暂时不太清楚，_error_flag 打印为 0, 不过调试发现是为 true 的

    printf("\n");
    printf("%f %d\n", power2(2, 3), _error_flag);
    printf("%f %d\n", power2(-2, 3), _error_flag);
    printf("%f %d\n", power2(2, -3), _error_flag);
    printf("%f %d\n", power2(2, 0), _error_flag);
    printf("%f %d\n", power2(0, 0), _error_flag);
    printf("%f %d\n", power2(0, 4), _error_flag);
    printf("%f %d\n", power2(0, -4), _error_flag);

    return 0;
}