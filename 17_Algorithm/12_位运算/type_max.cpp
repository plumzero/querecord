
// 获取某个类型的最值，如 int 类型的最大值为 2147483647，最小值为 -2147483648

#include <stdio.h>
#include <iostream>

// 需要对 取反，二进制编码表示(补码)，移位操作 有初步的了解

// 另外，测试中发现，在进行类型转换时，相比 C 语言中的 (type)val 形式，使用 static_cast<type>(val) 可以得到更期望的结果
int main()
{
    // int 类型
    printf("int max: %d\n", ((unsigned int)~0) >> 1);
    printf("int min: %d\n", (int)1 << 31);  // 符合期望

    // long 类型
    printf("long max: %ld\n", ((unsigned long)~0) >> 1);
    printf("long min: %ld\n", (long)1 << 63);   // 符合期望

    // char 类型
    printf("char max: %d\n", static_cast<char>(((unsigned char)~0) >> 1));
    printf("char min: %d\n", static_cast<char>(1 << 7));
    // 不妨打开如下注释进行对比
    // printf("unexpected char min: %d\n", (char)1 << 7);   // 不符合期望

    // short 类型
    printf("short max: %d\n", static_cast<short>(((unsigned short)~0) >> 1));
    printf("short min: %d\n", static_cast<short>(1 << 15));
    // 不妨打开如下注释进行对比
    // printf("unexpected short min: %d\n", (short)1 << 15);    // 不符合期望

    return 0;
}