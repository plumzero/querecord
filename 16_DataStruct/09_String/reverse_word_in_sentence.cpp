
// 58 1 翻转字符串

// 问题:
// 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
// 为简单起见，标点符号和普通字母一样处理。
// 例如，输入字符串 "I am a student.", 则输出 "student. a am I" 。

// 分析:
// 先翻转整个字符串，再翻转每个单词。

#include <stdio.h>
#include <string.h>

// 先定义一个函数，传入两个参数，分别指向要翻转字符串的首个字节及最后一个字节
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

void reverse_sentence(char* str)
{
    // assert(str != nullptr);

    int len = strlen(str);

    reverse(str, str + len - 1);

    char* pb = str;
    char* pe = str;
    while (*pb != '\0') {
        if (*pb == ' ') {
            pb++;
            pe++;
        } else if (*pe == ' ' || *pe == '\0') {
            reverse(pb, pe - 1);
            pb = pe;
        } else {
            pe++;
        }
    }
}

int main()
{
    char str[] = "I am a student.";

    reverse_sentence(str);

    printf("%s\n", str);

    return 0;
}