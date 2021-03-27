
#include <iostream>
#include <string>
#include <regex>

/**
 *  \\b(sub)([^ ]*)
 *   \b boundary 边界
 *   以 sub 开头，捕获 sub 分组，及 sub 后直到遇到空白字符为止的字符串分组
 */

int main ()
{
    {
        /** [1] std::regex_search 用法 */
        std::smatch sm;
        std::regex pattern("\\b(sub)([^ ]*)");
        std::string s("this subject has a submarine as a subsequence");
        
        size_t i;
        while (std::regex_search(s, sm, pattern)) {
            std::cout << "prefix:" << sm.prefix().str() << std::endl;
            std::cout << "match :";
            for (i = 0; i < sm.size(); i++) {
                std::cout << "[" << sm[i] << "] ";
            }
            std::cout << std::endl;
            
            std::cout << "suffix:" << sm.suffix().str() << std::endl << std::endl;

            s = sm.suffix().str();
        }
    }
    
    return 0;
}