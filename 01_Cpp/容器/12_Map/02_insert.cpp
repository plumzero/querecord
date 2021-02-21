
#include <iostream>
#include <map>

int main()
{
    {
        std::map<std::string, size_t> people {
            { "Ann", 25 },
            { "Bill", 46 },
            { "Jack", 32 },
            { "Jill", 32 }
        };
        
        for (const auto & kv : people) {
            std::cout << kv.first << "=>" << kv.second << ", ";
        }
        std::cout << std::endl;
        
        std::cout << std::boolalpha;
        std::pair<std::map<std::string, size_t>::iterator, bool> ret_pr;
        
        // 插入已有键
        ret_pr = people.insert(std::make_pair("Bill", 48));
        std::cout << ret_pr.first->first << " " << ret_pr.first->second << " " << ret_pr.second << std::endl;
        
        for (const auto & kv : people) {
            std::cout << kv.first << "=>" << kv.second << ", ";
        }
        std::cout << std::endl;
        
        // 插入先前不存在的键
        ret_pr = people.insert(std::make_pair("Fred", 22));
        std::cout << ret_pr.first->first << " " << ret_pr.first->second << " " << ret_pr.second << std::endl;
        
        for (const auto & kv : people) {
            std::cout << kv.first << "=>" << kv.second << ", ";
        }
        std::cout << std::endl;
    }
    
    // 列表初始化
    {
        std::map<std::string, size_t> crowd {
            { "May", 55 },
            { "Pat", 66 },
            { "Al", 22 },
            { "Ben", 44 }
        };
        
        crowd.insert({ {"Bert", 44}, {"Ellen", 99} });

        for (const auto & kv : crowd) {
            std::cout << kv.first << "=>" << kv.second << ", ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}