// regex_replace example
#include <iostream>
#include <string>
#include <regex>
#include <iterator>

int main ()
{
    std::string s("there is a subsequence in the string\n");
    std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

    // s 中满足匹配 e 的字符串使用 "sub-$2" 替换
    std::cout << std::regex_replace(s, e, "sub-$2");

    // 将 s 复制到 result 中，遇到满足匹配 e 的字符串，使用 "$2" 替换
    // 不会对原 s 的内容有改变
    std::string result;
    std::regex_replace(std::back_inserter(result), s.begin(), s.end(), e, "$2");
    std::cout << result;

    // s 中不满足匹配的字符串不再返回，只返回满足匹配并替换其之后的字符串
    std::cout << std::regex_replace(s, e, "$1 and $2", std::regex_constants::format_no_copy);
    std::cout << std::endl;

    return 0;
}