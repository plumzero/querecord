
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>


int main()
{
    {
        std::set<std::string> words1 { "one", "two", "three", "four", "five", "six" };
        std::set<std::string> words2 { "four", "two", "seven" };
        std::multiset<std::string> wordrs3;
        
        std::cout << std::boolalpha
                  << std::includes(std::begin(words1), std::end(words1),
                                   std::begin(words2), std::end(words2))
                  << std::endl;
        
        std::cout << std::boolalpha
                  << std::includes(std::begin(words1), std::end(words1),
                                   std::begin(words2), std::begin(words2))
                  << std::endl;

    }

    return 0;
}