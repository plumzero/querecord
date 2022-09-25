
// 48 最长不含重复字符的子字符串

// 问题: 请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。
// 说明: 字符串中只包含 'a'~'z' 的字符。
// 例如，在字符串 "arabcacfr" 中，最长的不含重复字符的子字符串是 "acfr", 长度为 4

// 这种应该算是一类题了

// 分析:
// 可以借鉴滑动窗口的方法，在左侧设置一个哨兵，初始化为 -1。在遍历的过程中出现重复字符时，
// 移动这个哨兵将上次出现的该字符及其左侧字符全部滑出。这样滑动窗口中的字符都是不重复的字符。


#include <stdio.h>
#include <algorithm>

int longest_substring(const char* str)
{
    int hash[26];
    for (int i = 0; i < 26; i++) {
        hash[i] = -1;
    }
    
    int len = -1;
    while (str[++len]);
    
    int longest = 0;
    int pos = -1;
    
    for (int i = 0; i < len; i++) {
        int key = str[i] - 'a';
        if (hash[key] >= 0) {
            pos = std::max(hash[key], pos);
        }
        hash[key] = i;
        longest = std::max(longest, i - pos);
    }
    
    return longest;
}

int main()
{
    printf("%d\n", longest_substring("arabca"));
    printf("%d\n", longest_substring("arabcacfr"));
    printf("%d\n", longest_substring("arabcacfrg"));

    return 0;
}