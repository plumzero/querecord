
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
    // emplace 添加
    {
        std::priority_queue<SS, std::vector<SS>, decltype(CompS)> ps { CompS };
        ps.emplace(new std::string("one"));
        ps.emplace(new std::string("two"));
        ps.emplace(new std::string("three"));
        ps.emplace(new std::string("four"));
        
        
        std::priority_queue<US, std::vector<US>, decltype(CompU)> pu { CompU };
        pu.emplace(new std::string("one"));
        pu.emplace(new std::string("two"));
        pu.emplace(new std::string("three"));
        pu.emplace(new std::string("four"));
    }
    
    // push 添加
    {
        std::priority_queue<SS, std::vector<SS>, decltype(CompS)> ps { CompS };
        ps.push(std::make_shared<std::string>("one"));
        ps.push(std::make_shared<std::string>("two"));
        ps.push(std::make_shared<std::string>("three"));
        ps.push(std::make_shared<std::string>("four"));
        
        
        std::priority_queue<US, std::vector<US>, decltype(CompU)> pu { CompU };
        pu.push(std::unique_ptr<std::string>(new std::string("one")));
        pu.push(std::unique_ptr<std::string>(new std::string("two")));
        pu.push(std::unique_ptr<std::string>(new std::string("three")));
        pu.push(std::unique_ptr<std::string>(new std::string("four")));
    }
   
    return 0;
}