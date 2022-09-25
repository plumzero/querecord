
// s15 字符串中的所有变位词

// 问题:
// 输入字符串 s1 和 s2 

#include <stdio.h>
#include <string.h>
#include <vector>

// s2 字符串
// s1 变位词
std::vector<int> find_anagrams(const char* s2, const char* s1)
{
    // assert(s2 != nullptr && s1 != nullptr);

    int hash[26] = { 0 };
    
    int len1 = strlen(s1);
    for (int i = 0; i < len1; i++) {
        int key = s1[i] - 'a';
        hash[key]--;
    }

    std::vector<int> vec;

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
            vec.push_back(pos);
        }
    }

    return vec;
}

int main()
{
    std::vector<int> vec = find_anagrams("cbadabacg", "abc");

    for (auto & ele: vec) {
        printf("%d\n", ele);
    }

    return 0;
}