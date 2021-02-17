
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
    {
        std::list<std::string> words { "one", "two", "two", "two", "three", "four", "four" };
        
        words.unique();
        
        std::cout << words.size() << std::endl;
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(words.begin(), words.end(), oit);     // one two three four
        std::cout << std::endl;
    }
    
    return 0;
}