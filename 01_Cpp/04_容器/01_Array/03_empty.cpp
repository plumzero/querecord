
#include <iostream>
#include <array>

int main()
{
    {
        std::array<double, 1> values;
        
        if (values.empty()) {
            std::cout << "array<double, 1> has no elements." << std::endl;
        } else {
            std::cout << "array<double, 1> has " << values.size() << " elements." << std::endl; 
        }
    }
    
    {
        std::array<double, 0> values;
        
        if (values.empty()) {
            std::cout << "array<double, 0> has no elements." << std::endl;
        } else {
            std::cout << "array<double, 0> has " << values.size() << " elements." << std::endl; 
        }
    }
    
    return 0;
}