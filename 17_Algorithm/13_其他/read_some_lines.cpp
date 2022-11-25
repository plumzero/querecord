
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

// 随机读取文件中的某几行
std::vector<std::string> read_some_lines(const std::string& filename)
{
    std::random_device rd;
    std::default_random_engine rng { rd() };
    
    std::ifstream ifs(filename, std::ifstream::in | std::ifstream::binary);
    if (! ifs.is_open()) {
        return {};
    }

    int k = 5;  // 取 5 行

    int i = 0;
    std::vector<std::string> selecteds;
    selecteds.push_back("");        // 填充一个空串，下标从 1 开始
    char buf[1024] = {0};

    while (! ifs.eof()) {
        i = i + 1;
        memset(buf, 0, sizeof(buf));
        ifs.getline(buf, sizeof(buf));
        if (i <= k) {
            selecteds.push_back(std::string(buf, strlen(buf)));
        } else {
            std::uniform_int_distribution<> values { 1, i };
            int j = values(rng);
            if (j <= k) {
                selecteds[j] = std::string(buf, strlen(buf));
            }
        }
    }

    ifs.close();

    return std::move(selecteds);
}

int main()
{
    const std::string filename = "lines.txt";
    // write_lines(filename);   // 注意去掉空行

    std::vector<std::string> vec = read_some_lines(filename);
    for (size_t i = 1; i < vec.size(); i++) {
        std::cout << "line: " << vec[i] << std::endl;
    }

    return 0;
}