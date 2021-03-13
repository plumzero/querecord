
#include <iostream>
#include <list>
#include <algorithm>

int main()
{
    // lower_bound upper_bound
    {
        std::list<int> values { 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
        
        values.sort();
        
        int wanted { 22 };
		
		std::cout << "The lower bound for " << wanted
				  << " is " << *std::lower_bound(std::begin(values), std::end(values), wanted)
				  << std::endl;
		
		std::cout << "The upper bound for " << wanted
				  << " is " << *std::upper_bound(std::begin(values), std::end(values), wanted)
				  << std::endl;
    }

    return 0;
}