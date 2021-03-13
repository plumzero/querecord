
#include <iostream>
#include <list>
#include <algorithm>

int main()
{
    // default: <
    {
        std::list<int> values { 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
        
        values.sort();
        
        int wanted { 22 };
        
        if (std::binary_search(std::begin(values), std::end(values), wanted)) {
            std::cout << wanted << " is definitely in there - somethere..." << std::endl;
        } else {
            std::cout << wanted << " cannot be found - maybe you got it wrong..." << std::endl;
        }
    }
    
    // own defined: >
    {
        std::list<int> values { 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
        
        auto predicate = [](int a, int b) { return a > b; };
        
        values.sort(predicate);
        
        int wanted { 22 };
        
        if (std::binary_search(std::begin(values), std::end(values), wanted, predicate)) {
            std::cout << wanted << " is definitely in there - somethere..." << std::endl;
        } else {
            std::cout << wanted << " cannot be found - maybe you got it wrong..." << std::endl;
        }
    }

    return 0;
}