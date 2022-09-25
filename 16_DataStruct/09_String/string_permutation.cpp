
// 38 字符串的排列

// 问题:
// 输入一个字符串，打印出该字符中字符的所有排列。
// 例如，输入字符串 abc, 则打印出由字符 a, b, c 所能排列出来的所有字符串 abc, acb, bac, bca, cab, cba

// 分析:
// 将字符串当作数组来处理。
// 假设数组长度为 n, 元素为 a1,a2,...,an, 如果想要求这 n 个数组元素的全排列，那就相当于求
// a1 固定时，a2,a3,...,an 的全排列集合; a2 固定时，a1,a3,...,an 的全排列集合;... an 固定时，a1,a2,...,a(n-1) 的全排列集合的汇总
// 而每个集合又可以分为更小的集合...

#include <stdio.h>

void permutation(char* str, int start, int end)
{
    // assert(str != nullptr);

    if (start == end) {
        printf("%s\n", str);
        return ;
    }

    for (int i = start; i <= end; i++) {
        char ch = str[start];
        str[start] = str[i];
        str[i] = ch;
        permutation(str, start + 1, end);
        ch = str[start];
        str[start] = str[i];
        str[i] = ch;
    }
}

int main()
{
    char str[] = "abc";
    int len = -1;
    while (str[++len]);

    // printf("%d\n", len);
    permutation(str, 0, len - 1);

    return 0;
}
