
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector<int> funcVec()
{
    return { 1, 3, 5, 7, 9 };
}

void funcMap(const std::map<std::string, std::string>& mp)
{
    for (const auto & kv : mp) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}
int main()
{
    /** [1] 返回值为容器时更加方便 */
    for (const auto & ele : funcVec()) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
    
    /** [2] 入参更加方便 */
    funcMap({ { "Hello World!", "C++" } });
    
    return 0;
}
