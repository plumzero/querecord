
#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string fnames[] = { "foo.txt", "bar.txt", "baz.dat", "zoidberg" };
    std::regex txt_pattern("[a-z]+\\.txt");
    
    /** [1] 检测子匹配 */
    std::cout << std::boolalpha;
    for (const auto & fname : fnames) {
        std::cout << fname << ": " << std::regex_match(fname, txt_pattern) << std::endl;
    }
    
    /** [2] 提取子匹配 */
    std::regex pattern("([a-z]+)\\.txt");
    for (const auto & fname : fnames) {
        std::smatch sm;
        if (std::regex_match(fname, sm, pattern)) {
            if (sm.size() == 2) {
                std::ssub_match subm0 = sm[0];
                std::ssub_match subm1 = sm[1];
                std::cout << subm0.str() << " has a base of: " 
                          << subm1.str() << std::endl;
            }
        }
    }
    
    /** [2] 提取多个子匹配 */
    std::regex patterns("([a-z]+)\\.([a-z]+)");
    for (const auto & fname : fnames) {
        std::smatch sm;
        if (std::regex_match(fname, sm, patterns)) {
            if (sm.size() == 3) {
                std::ssub_match subm0 = sm[0];
                std::ssub_match subm1 = sm[1];
                std::ssub_match subm2 = sm[2];
                std::cout << subm0.str() << " is consisted of: " 
                          << subm1.str() << " and " << subm2.str() << std::endl;
            }
        }
    }

    return 0;
}
