
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <string>


int main()
{
    {
        std::set<int> numbers { 8, 7, 6, 5, 4, 3, 2, 1 };
        
        std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout, " "));
        
        std::cout << std::endl;
    }

    {
        std::set<std::string, std::greater<std::string>> words {
            "one", "two", "three", "four", "five", "six", "seven", "eight"
        };
        
        std::copy(std::begin(words), std::end(words), std::ostream_iterator<std::string>(std::cout, " "));
        
        std::cout << std::endl;
    }

    {
        std::set<std::string> words {
            "one", "two", "three", "four", "five", "six", "seven", "eight"
        };
        
        std::set<std::string> words2{std::begin(words), std::end(words)};
        
        (void) words2;
    }

    return 0;
}