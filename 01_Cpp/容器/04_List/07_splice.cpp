
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>

int main()
{
    // 两参数重载: 剪切整个容器
    {
        std::list<std::string> des { "three", "six", "eight" };
        std::list<std::string> src { "seven", "four", "nine" };
        
        des.splice(++std::begin(des), src);
      
        std::cout << src.size() << ": ";
        std::ostream_iterator<std::string> oit_src(std::cout, " ");
        std::copy(src.begin(), src.end(), oit_src);
        std::cout << std::endl; // 0: 
      
        std::cout << des.size() << ": ";
        std::ostream_iterator<std::string> oit_des(std::cout, " ");
        std::copy(des.begin(), des.end(), oit_des);
        std::cout << std::endl; // 6: three seven four nine six eight
    }
    
    
    // 三参数重载: 剪切单个元素
    {
        std::list<std::string> des { "three", "six", "eight" };
        std::list<std::string> src { "seven", "four", "nine" };
        
        des.splice(++std::begin(des), src, ++std::begin(src));
      
        std::cout << src.size() << ": ";
        std::ostream_iterator<std::string> oit_src(std::cout, " ");
        std::copy(src.begin(), src.end(), oit_src);
        std::cout << std::endl; // 2: seven nine
      
        std::cout << des.size() << ": ";
        std::ostream_iterator<std::string> oit_des(std::cout, " ");
        std::copy(des.begin(), des.end(), oit_des);
        std::cout << std::endl; // 4: three four six eight
    }
    
    // 四参数重载: 剪切一段元素
    {
        std::list<std::string> des { "three", "six", "eight" };
        std::list<std::string> src { "seven", "four", "nine" };
        
        des.splice(++std::begin(des), src, ++std::begin(src), std::end(src));
      
        std::cout << src.size() << ": ";
        std::ostream_iterator<std::string> oit_src(std::cout, " ");
        std::copy(src.begin(), src.end(), oit_src);
        std::cout << std::endl; // 1: seven
      
        std::cout << des.size() << ": ";
        std::ostream_iterator<std::string> oit_des(std::cout, " ");
        std::copy(des.begin(), des.end(), oit_des);
        std::cout << std::endl; // 5: three four nine six eight
    }
    
    return 0;
}