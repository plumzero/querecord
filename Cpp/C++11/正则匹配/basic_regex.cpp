
#include <iostream>
#include <string>
#include <regex>

int main()
{
    {
        /** [1] cmatch 用法 */
        std::cout << "cmatch 用法:" << std::endl;
        std::cmatch cm;
        std::basic_regex<char> pattern("(sub)(.*)");
        
        std::regex_match("subject", cm, pattern);
        
        size_t i;
        std::cout << cm.size() << " results." << std::endl;
        for (i = 0; i < cm.size(); i++) {
            std::cout << "[" << cm.length(i) << " : " << cm.str(i) << "] "; 
        }
        std::cout << std::endl;
    }
    
    {
        /** [2] smatch 用法 */
        std::cout << "smatch 用法:" << std::endl;
        std::smatch sm;
        std::basic_regex<char> pattern("(sub)(.*)");
        std::string s("subject");
        
        std::regex_match(s, sm, pattern);
        
        size_t i;
        std::cout << sm.size() << " results." << std::endl;
        for (i = 0; i < sm.size(); i++) {
            std::cout << "[" << sm.length(i) << " : " << sm.str(i) << "] "; 
        }
        std::cout << std::endl;
    }
    
    {
        /** [3] 迭代器的用法 */
        std::cout << "迭代器用法:" << std::endl;
        std::smatch sm;
        std::basic_regex<char> pattern("(sub)(.*)");
        std::string s("subject");
        
        std::regex_match(s, sm, pattern);
        
        for (const auto & ele : sm) {
            std::cout << "[" << ele << "] ";
        }
        std::cout << std::endl; 
    }
    
    return 0;
}
