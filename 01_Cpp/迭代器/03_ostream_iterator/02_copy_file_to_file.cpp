
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <cassert>

int main ()
{
    // 流实现文件拷贝到字符串
    {
        std::ifstream ifs("srcfile", std::ifstream::in | std::ifstream::binary);
        assert(ifs.is_open());
        
        std::string text;
        
        std::copy(std::istream_iterator<char>(ifs >> std::noskipws),
                  std::istream_iterator<char>(),
                  std::back_inserter(text));
        
        // std::cout << text << std::endl;
        
        ifs.close();
    }
    
    // 文件拷贝
    {
        std::ifstream ifs("srcfile", std::ifstream::in | std::ifstream::binary);
        assert(ifs.is_open());
        
        std::ofstream ofs("desfile", std::ofstream::out | std::ofstream::binary);
        assert(ofs.is_open());
        
        std::copy(std::istream_iterator<char>(ifs >> std::noskipws),
                  std::istream_iterator<char>(),
                  std::ostream_iterator<char>(ofs));  

        ifs.close();
        ofs.close();                  
    }
    
    return 0;
}