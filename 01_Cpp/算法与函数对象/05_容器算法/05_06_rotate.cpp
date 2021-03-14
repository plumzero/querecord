
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
    {
        std::vector<std::string> words { "one", "two", "three", "four", "five", "six", "seven", "eight" };
        
        std::rotate(std::begin(words), std::begin(words) + 3, std::end(words));
        std::copy(std::begin(words), std::end(words), std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;     
    }
    
    // 局部旋转
    {
        std::vector<std::string> words { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
        
        auto begin_iter = std::find(std::begin(words), std::end(words), "two");
        auto end_iter = std::find(std::begin(words), std::end(words), "eight");
        auto mid_iter = std::find(std::begin(words), std::end(words), "five");
        
        std::rotate(begin_iter, mid_iter, end_iter);
        
        std::copy(std::begin(words), std::end(words), std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;
    }
    
    // rotate_copy
    {
        std::vector<std::string> words { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
        
        auto begin_iter = std::find(std::begin(words), std::end(words), "two");
        auto end_iter = std::find(std::begin(words), std::end(words), "eight");
        auto mid_iter = std::find(std::begin(words), std::end(words), "five");
        std::vector<std::string> words_copy;
        
        std::rotate_copy(begin_iter, mid_iter, end_iter, std::back_inserter(words_copy));
        
        std::copy(std::begin(words_copy), std::end(words_copy), std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;
    }
    
    return 0;
}