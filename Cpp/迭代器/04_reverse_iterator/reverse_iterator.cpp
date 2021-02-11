
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

int main ()
{
    // rbegin and self-operation test
    {
        std::vector<int> nums{ 100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        
        std::vector<int>::reverse_iterator itRbegin = nums.rbegin();
        
        std::cout << *itRbegin << std::endl;        // 10
        
        itRbegin++;
        
        std::cout << *itRbegin << std::endl;        // 9
    }
    
    // rend and self-operation test
    {
        std::vector<int> nums{ 100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        
        std::vector<int>::reverse_iterator itRend = nums.rend();
        
        // std::cout << *itRend << std::endl;          // 指向哨兵位，不建议解引用
        
        itRend--;
        
        std::cout << *itRend << std::endl;          // 100
    }
    
    // .base() test
    {
        std::vector<int> nums{ 100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        
        std::vector<int>::iterator itFirst = nums.rend().base();
        
        std::cout << *itFirst << std::endl;          // 100
    }

    return 0;
}