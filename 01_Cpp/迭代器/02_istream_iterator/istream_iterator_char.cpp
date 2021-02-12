
#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

int main ()
{
    std::ifstream ifs("istream_iterator.txt", std::ifstream::in | std::ifstream::binary);
    assert(ifs.is_open());
    
    std::vector<char> values;
    
    values.insert(std::begin(values),
                  std::istream_iterator<char>(ifs),
                  std::istream_iterator<char>());
    
    for (const auto & ele : values) {
        std::cout << static_cast<int>((unsigned char)ele) << " ";
    }
    std::cout << std::endl;
 
    return 0;
}