
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <cmath>

constexpr int Pow(int base, int exp) noexcept
{
  return std::pow(base, exp);
}

int main()
{
  // caculate at compile time
  {
    std::cout << Pow(2, 4) << std::endl;
  }

  // caculate at runtime
  {
    std::vector<int> wvec{7, 2};
    std::ofstream ofs("file.txt", std::ofstream::out | std::ofstream::binary);
    std::ostream_iterator<int> oit(ofs, " ");
    std::copy(wvec.begin(), wvec.end(), oit);
    ofs.close();

    std::vector<int> rvec;
    std::ifstream ifs("file.txt", std::ifstream::in | std::ifstream::binary);
    rvec.insert(std::begin(rvec), std::istream_iterator<int>(ifs), std::istream_iterator<int>());
    ifs.close();

    // 模拟从数据库中读取
    int base = rvec[0];
    int exp = rvec[1];
    std::cout << Pow(base, exp) << std::endl;
  }

  return 0;
}