
// s14 字符串中的变位词

// 问题:
// 输入字符串 s1 和 s2，如何判断字符吕 s2 中是否包含字符串 s1 的某个变位词? 
// 如果字符串 s2 中包含字符串 s1 的某个变位词，则字符串 s1 至少有一个变位词
// 是字符串 s2 的子字符串。
// 假设两个字符串中只包含英文小写字母。
// 例如，字符串 s1 为 "ac", 字符串 s2 为 "dgcaf"，由于字符串 s2 中包含字符
// 串 s1 的变位词 "ca"，因此输出为 true。如果字符串 s1 为 "ab", 字符串 s2
// 为 "dgcaf"，则输出为 false 。

// 分析:
// 尝试使用滑动窗口方法

#include <stdio.h>
#include <string.h>

bool check_anagram(const char* s2, const char* s1)
{
    // assert(s1 != nullptr && s2 != nullptr);
    int hash[26] = { 0 };

    int len1 = strlen(s1);
    for (int i = 0; i < len1; i++) {
        int key = s1[i] - 'a';
        hash[key]--;
    }

    int pos = 0;
    int len2 = strlen(s2);

    for (int i = 0; i < len2; i++) {
        int key = s2[i] - 'a';
        hash[key]++;
        while (hash[key] > 0) {
            int k = s2[pos] - 'a';
            hash[k]--;
            pos++;
        }
        if (i - pos + 1 == len1) {
            return true;
        }
    }

    return false;
}

int main()
{
    printf("%d\n", check_anagram("dgcaf", "ac"));
    printf("%d\n", check_anagram("dgcaf", "ab"));

    return 0;
}