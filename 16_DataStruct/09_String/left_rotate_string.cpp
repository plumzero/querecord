
// 58 2 左旋转字符串

// 问题:
// 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
// 定义一个函数实现字符串的左旋转操作的功能。
// 比如，输入字符串 "abcdefg" 和数字 2，该函数将返回左旋转两位得到的结果 "cdefgab"

// 分析:
// 比如对于字符串 "abcdefg", 按照给定的数字 2 分成两个部分 "ab" 和 "cdefg"，将这两部分
// 分别左旋得到 "bagfedc"，之后对字符串整个旋转得到 "cdefgab"

#include <stdio.h>
#include <string.h>

void reverse(char* pb, char* pe)
{
    // assert(pb != nullptr && pe != nullptr);

    while (pb < pe) {
        char ch = *pb;
        *pb = *pe;
        *pe = ch;
        pb++;
        pe--;
    }
}

void left_rotate(char* str, int n)
{
    // assert(str != nullptr && k >= 0);

    if (strlen(str) < n)
        return ;

    char* pb = str;
    char* pe = str + strlen(str) - 1;
    char* px = str + n - 1;

    reverse(pb, px);
    reverse(px + 1, pe);
    reverse(pb, pe);
}

int main()
{
    {
        char str[] = "abcdefg";
        left_rotate(str, 2);
        printf("%s\n", str);
    }

    {
        char str[] = "abcdefg";
        left_rotate(str, 0);
        printf("%s\n", str);
    }

    {
        char str[] = "abcdefg";
        left_rotate(str, 10);
        printf("%s\n", str);
    }

    return 0;
}
