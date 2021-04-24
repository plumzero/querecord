
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

int main ()
{
    // 写入标准输出
    {
        std::vector<int> ivec{'A', 'C', 'M', 'i', 'L', 'a', 'n' };
        
        std::copy(ivec.begin(), ivec.end(), std::ostreambuf_iterator<char>(std::cout));
        std::cout << std::endl;
    }
    
    // 写入文件
    {
        std::vector<int> ivec{'A', 'C', 'm', 'i', 'l', 'a', 'n' };
        std::ofstream ofs("write.txt", std::ofstream::out | std::ofstream::binary);
        
        std::copy(ivec.begin(), ivec.end(), std::ostreambuf_iterator<char>(ofs));
        
        ofs.close();
    }

    return 0;
}