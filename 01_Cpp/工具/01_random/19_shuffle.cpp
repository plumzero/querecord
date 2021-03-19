
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>

#include <cmath>

int main()
{
    std::random_device rd;
    std::mt19937 rng { rd() };
    std::vector<std::string> words { "one", "two", "three", "four", "five", "six", "seven", "eight" };
    
    for (size_t i{}; i < 4; i++) {
        std::shuffle(std::begin(words), std::end(words), rng);
        
        std::for_each(std::begin(words), std::end(words), [](const std::string& word){
            std::cout << std::setw(8) << std::left << word;
        });
        std::cout << std::endl;
    }
    
    return 0;
}