
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
    
    std::vector<int> values;
    
    values.insert(std::begin(values),
                  std::istream_iterator<int>(ifs),
                  std::istream_iterator<int>());
    
    for (const auto & ele : values) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
 
    return 0;
}