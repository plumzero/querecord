
#include <iostream>
#include <array>

int main()
{
    {
        std::array<double, 10> values { 0.5, 1.0, 1.5, 2.0 };
        
        for (const auto & ele : values) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    {
        std::array<double, 10> values { 0.5, 1.0, 1.5, 2.0 };
        
        values.fill(3.1415926);
        
        for (const auto & ele : values) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}