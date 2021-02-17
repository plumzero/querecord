
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
    {
        std::vector<std::string> words { "one", "none", "some", "all", "none", "most", "many" };
        
        auto iter = std::remove(std::begin(words), std::end(words), "none");
        
        // remove 移除不会删除容器中的元素，而是通过匹配元素右边的元素来覆盖匹配元素的方式移除元素
        // 在这里，remove 操作后，容器中元素个数仍为 7,  最后两个元素被替换成了空字符串对象
        std::cout << words.size() << std::endl;
        
        // 可以使用成员函数 erase() 删除多余元素
        words.erase(iter, std::end(words));
        
        std::cout << words.size() << std::endl;
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(words.begin(), words.end(), oit);
        std::cout << std::endl;
    }
    
    // 简化写法
    {
        std::vector<std::string> words { "one", "none", "some", "all", "none", "most", "many" };
        
        words.erase(std::remove(std::begin(words), std::end(words), "none"), std::end(words));
        
        std::cout << words.size() << std::endl;
        std::ostream_iterator<std::string> oit(std::cout, " ");
        std::copy(words.begin(), words.end(), oit);
        std::cout << std::endl;
    }
    
    return 0;
}