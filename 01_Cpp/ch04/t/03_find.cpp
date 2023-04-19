
#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

int main ()
{
    std::ifstream ifs("word.txt", std::ifstream::in | std::ifstream::binary);
    assert(ifs.is_open());
    
    std::string word {"algorithmic"};
    auto end_iter = std::istream_iterator<std::string>{};
    
    decltype(end_iter) find_iter;
    find_iter = std::find(std::istream_iterator<std::string>(ifs), end_iter, word);
    if (find_iter != end_iter) {
        std::cout << "Find " << *find_iter << std::endl;
    } else {
        std::cout << "Not find " << word << std::endl;
    }
    
    word = "Algorithmic";
    find_iter = std::find(std::istream_iterator<std::string>(ifs), end_iter, word);
    if (find_iter != end_iter) {
        std::cout << "Find " << *find_iter << std::endl;
    } else {
        std::cout << "Not find " << word << std::endl;
    }

    return 0;
}