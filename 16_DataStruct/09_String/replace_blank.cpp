
// 05 替换空格

// 问题:
// 把字符串中的每个空格替换成 "%20"。
// 例如输入 "We are happy.", 则输出 "We%20are%20happy."

// 分析:
// 略

#include <stdio.h>

// size 为容量
void replace_blank(char str[], int size)
{
    int len = -1;
    int count_of_blank = 0;
    while (str[++len]) {
        if (str[len] == ' ') {
            count_of_blank++;
        }
    }
    
    int new_len = len + count_of_blank * 2;
    // assert(new_len < size);
    int old_index = len - 1;
    int new_index = new_len - 1;
    while (old_index != new_index) {
        if (str[old_index] == ' ') {
            str[new_index--] = '0';
            str[new_index--] = '2';
            str[new_index--] = '%';
        } else {
            str[new_index--] = str[old_index];
        }
        old_index--;
    }
}

int main()
{
    {
        char str[32] = { "We are happy." };
        replace_blank(str, 32);
        printf("%s\n", str);
    }

    {
        char str[32] = { " We are happy." };
        replace_blank(str, 32);
        printf("%s\n", str);
    }

    {
        char str[32] = { "We are  happy. " };
        replace_blank(str, 32);
        printf("%s\n", str);
    }

    return 0;
}