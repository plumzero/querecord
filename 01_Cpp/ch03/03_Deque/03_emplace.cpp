
#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
    // emplace_back
    {
        std::deque<std::string> words;
        
        std::string str { "alleged" };
        
        words.emplace_back(str, 2, 3);
        
        std::cout << words.back() << std::endl; // "leg"        
    }
    
    // emplace_front
    {
        std::deque<std::string> words{ "first", "second" };
        
        words.emplace_front("zero");
        
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(words.begin(), words.end(), oit);     // "zero" "first" "second"
        std::cout << std::endl;
    }
    
    // emplace
    {
        std::deque<std::string> words{ "first", "second" };
        
        auto iter = words.emplace(++std::begin(words), 5, 'A');
        words.emplace(++iter, "$$$$");
        
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(words.begin(), words.end(), oit);     // "first" "AAAAA" "$$$$" "second"
        std::cout << std::endl;
    }
    
    return 0;
}