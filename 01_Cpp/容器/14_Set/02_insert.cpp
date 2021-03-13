
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <string>

#include <cassert>

int main()
{
    {
        std::set<std::string, std::greater<std::string>> words {
            "one", "two", "three"
        };
        
        auto pr1 = words.insert("four");
        assert(pr1.second == true);
        
        auto pr2 = words.insert("two");
        assert(pr2.second == false);
        
        auto iter3 = words.insert(pr1.first, "seven");
        (void) iter3;
        
        words.insert({"five", "six"});
        
        std::string wrds[]{ "eight", "nine", "ten" };
        words.insert(std::begin(wrds), std::end(wrds));
        
        std::copy(std::begin(words), std::end(words), std::ostream_iterator<std::string>(std::cout, " "));
        
        std::cout << std::endl;
    }
    
    
    return 0;
}