
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
    // emplace_back
    {
        std::string str { "alleged" };
        
        std::vector<std::string> words;
        
        words.emplace_back(str, 2, 3);
        
        std::cout << words.back() << std::endl; // "leg"        
    }
    
    // emplace
    {
        std::vector<std::string> words{ "first", "second" };
        
        auto iter = words.emplace(++std::begin(words), 5, 'A');
        words.emplace(++iter, "$$$$");
        
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(words.begin(), words.end(), oit);     // "first" "AAAAA" "$$$$" "second"
    }
    
    return 0;
}