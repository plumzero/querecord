
#include <iostream>
#include <array>

int main()
{
    {
        std::array<double, 4> these { 1.0, 2.0, 3.0, 4.0 };
        std::array<double, 4> those { 1.0, 2.0, 3.0, 4.0 };
        std::array<double, 4> them  { 1.0, 3.0, 3.0, 2.0 };
        
        if (these == those) {
            std::cout << "these and those are equal." << std::endl;
        }
        
        if (those != them) {
            std::cout << "those and them are not equal." << std::endl;
        }
        
        if (those < them) {
            std::cout << "those are less than them." << std::endl;
        }
        
        if (them > those) {
            std::cout << "them are greater than those." << std::endl;
        }
    }
    
    return 0;
}