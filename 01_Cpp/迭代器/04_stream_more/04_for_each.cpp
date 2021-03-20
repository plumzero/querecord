
#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <algorithm>

int main ()
{
    std::ifstream ifs("word.txt", std::ifstream::in | std::ifstream::binary);
    assert(ifs.is_open());
    
    std::map<std::string, size_t> words_map;
    
    std::for_each(std::istream_iterator<std::string>(ifs),
                  std::istream_iterator<std::string>(),
                  [&words_map](const std::string& s){ words_map[s]++; });
    
    std::for_each(std::begin(words_map), std::end(words_map),
                  [](const std::pair<std::string, size_t>& pr) {
                      std::cout << pr.first << ": " << pr.second << std::endl;
                  });

    return 0;
}