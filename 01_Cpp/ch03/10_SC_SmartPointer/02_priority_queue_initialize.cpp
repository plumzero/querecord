
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

using SS = std::shared_ptr<std::string>;
using US = std::unique_ptr<std::string>;

auto CompS = [](const SS& p1, const SS& p2) { return *p1 < *p2; };
auto CompU = [](const US& p1, const US& p2) { return *p1 < *p2; };


int main()
{
    // 空初始化
    {
        std::priority_queue<SS, std::vector<SS>, decltype(CompS)> ps { CompS };
        
        std::priority_queue<US, std::vector<US>, decltype(CompU)> pu { CompU };
    }
    
    // 容器初始化
    {
        std::vector<SS> vs {
            std::make_shared<std::string>("one"),
            std::make_shared<std::string>("two"),
            std::make_shared<std::string>("three"),
            std::make_shared<std::string>("four")
        };
        std::priority_queue<SS, std::vector<SS>, decltype(CompS)> ps { CompS, vs };
        
        // unsupport !
        // std::vector<US> vu {
            // std::unique_ptr<std::string>(new std::string("one")),
            // std::unique_ptr<std::string>(new std::string("two")),
            // std::unique_ptr<std::string>(new std::string("three")),
            // std::unique_ptr<std::string>(new std::string("four"))
        // };
        // std::priority_queue<US, std::vector<US>, decltype(CompU)> pu { CompU, vu };
    }
   
    return 0;
}