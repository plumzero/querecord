
#include <iostream>
#include <deque>

int main()
{
    {
        std::deque<int> my_deque(10);   // 10 个元素，缺省值为 0
        (void) my_deque;
    }

    {
        std::deque<std::string> words { "one", "none", "some", "all", "none", "most", "many" };
        
        std::deque<std::string> words_copy{ words };
        
        (void) words_copy;
    }
    
    {
        std::deque<std::string> words { "one", "none", "some", "all", "none", "most", "many" };
        
        std::deque<std::string> words_part { std::begin(words), std::begin(words) + 5 };
        
        (void) words_part;
    }

    return 0;
}