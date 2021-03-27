
#include <cstdio>
#include <iostream>
#include <vector>

int main()
{
    {
		std::vector<int> values;
		
		values.reserve(5);
		
		std::cout << &*std::begin(values) << std::endl;
		
		for (int i = 0; i < 5; i++) {
			values.push_back(i);
		}
		std::cout << &*std::begin(values) << std::endl;
		
		values.push_back(10);
		std::cout << &*std::begin(values) << std::endl;
    }
        
    return 0;
}
