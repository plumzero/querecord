
// 对字符串的旋转操作描述如下: 例如对于 str = "123456"，它的所有旋转词为:
// "123456", "234561", "345612", "456123", "561234", "612345"
// 给定两个字符串 str1 和 str2, 实现判断 str1 是否是 str2 的旋转词 

#include <stdio.h>

// str2 原词
// str1 旋转词
bool func(const char* str2, const char* str1)
{
    const char* pb1 = str1;
    const char* pb2 = str2;
    while (*pb1 != *pb2)
        pb2++;
    while (*pb2 != '\0') {
        if (*pb1 != *pb2)
            return false;
        pb1++;
        pb2++;
    }
    pb2 = str2;
    while (*pb1 != '\0') {
        if (*pb1 != *pb2)
            return false;
        pb1++;
        pb2++;
    }
    return true;
}

int main()
{
    printf("%d\n", func("123456", "123456"));
    printf("%d\n", func("123456", "234561"));
    printf("%d\n", func("123456", "345612"));
    printf("%d\n", func("123456", "456123"));
    printf("%d\n", func("123456", "612345"));
    printf("%d\n", func("123456", "612354"));

    return 0;
}