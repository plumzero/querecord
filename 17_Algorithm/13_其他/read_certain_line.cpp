
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <iterator>
#include <numeric>
#include <string.h>

void write_lines(const std::string& filename)
{
    std::vector<int> vec(10);
    std::iota(std::begin(vec), std::end(vec), 1);
    
    std::ofstream ofs(filename, std::ofstream::out | std::ofstream::binary);

    std::ostream_iterator<int> oit(ofs, "\n");

    std::copy(vec.begin(), vec.end(), oit);

    ofs.close();
}

// 随机读取文件的某一行
std::string read_certain_line(const std::string& filename)
{
    std::random_device rd;
    std::default_random_engine rng { rd() };
    std::uniform_real_distribution<> values { 0.0, 1.0 };

    std::ifstream ifs(filename, std::ifstream::in | std::ifstream::binary);
    if (! ifs.is_open()) {
        return "";
    }

    double i = 0.0;
    std::string selected = "";
    char buf[1024] = {0};

    while (! ifs.eof()) {
        i = i + 1;
        memset(buf, 0, sizeof(buf));
        ifs.getline(buf, sizeof(buf));
        double r = values(rng);
        if (r < 1 / i) {
            selected = std::string(buf, strlen(buf));
        }
    }

    ifs.close();

    return selected;
}

int main()
{
    const std::string filename = "lines.txt";
    // write_lines(filename);   // 注意去掉空行

    for (int i = 0; i < 10; i++) {
        std::string line = read_certain_line(filename);
        std::cout << "line: " << line << std::endl;
    }

    return 0;
}