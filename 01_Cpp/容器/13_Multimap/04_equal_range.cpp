
#include <iostream>
#include <map>
#include <string>

int main()
{
    {
        std::multimap<std::string, size_t> people {
            { "Ann", 35 },
            { "Bill", 46 },
            { "Jack", 77 },
            { "Jack", 32 },
            { "Jill", 32 },
            { "Ann", 25 }
        };

        auto pair_iter = people.equal_range("Ann");
        if (pair_iter.first != std::end(people)) {  // 利用 pair_iter 中的第一个元素判断是否结束即可
            for (auto iter = pair_iter.first; iter != pair_iter.second; iter++) {
                std::cout << iter->first << " is " << iter->second << std::endl;
            }
        }
    }
    
    return 0;
}