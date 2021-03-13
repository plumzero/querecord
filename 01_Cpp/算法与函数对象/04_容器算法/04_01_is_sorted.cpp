
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

int main()
{
    // is_sorted: <
    {
        std::vector<int> numbers { 22, 7, 93, 45, 19 };
        std::vector<double> data { 1.5, 2.5, 3.5, 4.5 };
        
        std::cout << "numbers is "
                  << (std::is_sorted(std::begin(numbers), std::end(numbers)) ? "" : "not ")
                  << "in ascending sequence."
                  << std::endl;
                  
        std::cout << "data is "
                  << (std::is_sorted(std::begin(data), std::end(data)) ? "" : "not ")
                  << "in ascending sequence."
                  << std::endl;
    }
    
    // is_sorted: >
    {
        std::vector<int> numbers { 22, 7, 93, 45, 19 };
        std::vector<double> data { 1.5, 2.5, 3.5, 4.5 };
        
        std::cout << "numbers is "
                  << (std::is_sorted(std::begin(numbers), std::end(numbers)) ? "" : "not ")
                  << "in ascending sequence."
                  << std::endl;
                  
        std::cout << "data reversed is "
                  << (std::is_sorted(data.rbegin(), data.rend(), std::greater<double>()) ? "" : "not ")
                  << "in ascending sequence."
                  << std::endl;
    }
    
    // is_sorted_until: <
    {
        std::vector<std::string> pets { "cat", "chicken", "dog", "pig",  "llama", "coati", "goat" };
        
        std::cout << "The pets in ascending sequence are:\n";
        std::copy(std::begin(pets),
                  std::is_sorted_until(std::begin(pets), std::end(pets)),
                  std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;
    }
    
    // is_sorted_until: >
    {
        std::vector<std::string> pets { "dog", "coati", "cat", "chicken",  "pig", "llama", "goat" };
        
        std::cout << "The pets in descending sequence are:\n";
        std::copy(std::begin(pets),
                  std::is_sorted_until(std::begin(pets), std::end(pets), std::greater<std::string>()),
                  std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;
    }
    
    return 0;
}