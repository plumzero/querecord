
#include <iostream>
#include <array>
#include <stdexcept>

int main()
{
    {
        std::array<double, 5> values { 0.5, 1.0, 1.5, 2.0 };
                
        for (auto it = values.begin(); it != values.end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl; 
    }
        
    return 0;
}
