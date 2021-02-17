
#include <iostream>
#include <array>
#include <stdexcept>

int main()
{
    {
        std::array<double, 5> values { 0.5, 1.0, 1.5, 2.0 };
        
        values[4] = values[3] + 2.0 * values[1];
        
        for (const auto & ele : values) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
    
    {
        std::array<double, 5> values { 0.5, 1.0, 1.5, 2.0 };
        
        values.at(4) = values.at(3) + 2.0 * values.at(1);
        
        for (const auto & ele : values) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
    
    {
        std::array<double, 5> values { 0.5, 1.0, 1.5, 2.0 };
        try {
            values.at(5);
        }
        catch(const std::out_of_range& e) {
            std::cerr << "out of range exception catched" << std::endl;
        }
    }
    
    return 0;
}