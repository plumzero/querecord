
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <string>

#include <cassert>

int main()
{
    {
        std::set<std::pair<std::string, std::string>> names;
        
        auto pr = names.emplace("Lisa", "Carr");
        assert(pr.second == true);
        
        auto iter = names.emplace_hint(pr.first, "Joe", "King");
        
        (void) iter;
    }
    
    return 0;
}