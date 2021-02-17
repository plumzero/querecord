
#include <iostream>
#include <array>

int main()
{
    {        
        std::array<std::string, 5> words { "one", "two", "three", "four", "five" };
        std::cout << std::get<3>(words) << std::endl;   // Output words[3]
        // std::cout << std::get<6>(words) << std::endl;   // Compiler error message!
    }

    return 0;
}