
#include <queue>
#include <iostream>
#include <string>

int main()
{
    // 生成空 p 队列
    {
        std::priority_queue<std::string> words;
        
        (void) words;
    }
    
    // 通过迭代器初始化
    {
        std::string wrds[] { "one", "two", "three", "four" };
        std::priority_queue<std::string> words {std::begin(wrds), std::end(wrds)};
        
        (void) words;
    }
    
    // 指定其他"优先级"
    {
        std::string wrds[] { "one", "two", "three", "four" };
        std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> words {std::begin(wrds), std::end(wrds)};
        
        (void) words;
    }
    
    // 通过容器初始化
    {
        std::vector<int> values{ 21, 22, 12, 3, 24, 54, 56 };
        std::priority_queue<int> numbers { std::less<int>(), values };
        // 构造时，第一个参数是一个用来对元素排序的函数对象
        (void) numbers;
    }
    
    return 0;
}