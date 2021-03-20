
#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

int main ()
{
    std::ifstream ifs("word.txt", std::ifstream::in | std::ifstream::binary);
    assert(ifs.is_open());
    
    std::string word {"which"};
    
    int count = count_if(std::istream_iterator<std::string>(ifs),
                         std::istream_iterator<std::string>(),
                         [&word](const std::string& s) { return s == word; });
    
    std::cout << "total " << count << " " << word << std::endl;

    return 0;
}