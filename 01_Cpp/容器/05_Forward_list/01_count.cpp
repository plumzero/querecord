
#include <iostream>
#include <forward_list>
#include <iterator>

int main()
{
    std::forward_list<std::string> words { "three", "six", "eight" };
    
    auto count = std::distance(std::begin(words), std::end(words));
    
    std::cout << count << std::endl;
    
    return 0;
}