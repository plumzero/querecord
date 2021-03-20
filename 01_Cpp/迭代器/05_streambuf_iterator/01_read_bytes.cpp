
#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

int main ()
{
    // 读入 vector
    {
        std::ifstream ifs("read.txt", std::ifstream::in | std::ifstream::binary);
        assert(ifs.is_open());
        
        std::vector<char> values;
        
        std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(),
                  std::back_inserter(values));
        
        for (const auto & ele : values) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
        
        ifs.close();
    }
    
    // 读入 string
    {
        std::ifstream ifs("read.txt", std::ifstream::in | std::ifstream::binary);
        assert(ifs.is_open());
        
        std::string str;
        
        std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(),
                  std::back_inserter(str));
        
        std::cout << str << std::endl;

        ifs.close();
    }

    return 0;
}