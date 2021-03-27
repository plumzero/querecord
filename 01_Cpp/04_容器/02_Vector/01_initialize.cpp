
#include <iostream>
#include <array>
#include <vector>

int main()
{
    {
        std::vector<double> values(20);     // 20 个元素，默认初始值为 0
        (void) values;
    }

    {
        std::vector<long> values{20};       // 1 个元素，值为 20
        (void) values;
    }

    {
        std::vector<long> numbers(20, 99L); // 20 个元素，默认初始值为 99L
        (void) numbers;
    }

    {
        std::array<std::string, 5> words { "one", "two", "three", "four", "five" };
        std::vector<std::string> words_copy { std::begin(words), std::end(words) }; // 迭代器初始化
        (void) words;
        (void) words_copy;
    }
    
    {
        std::array<std::string, 5> words { "one", "two", "three", "four", "five" };
        std::vector<std::string> words_move { std::make_move_iterator(std::begin(words)),
                                              std::make_move_iterator(std::end(words)) }; // 移动迭代器初始化
        (void) words;
        (void) words_move;
    }
    
    return 0;
}