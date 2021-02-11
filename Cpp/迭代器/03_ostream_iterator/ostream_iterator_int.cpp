
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

int main ()
{
    std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8};
    std::ofstream ofs("ostream_iterator.txt", std::ofstream::out | std::ofstream::binary);

    std::ostream_iterator<int> oit(ofs, ", ");
    std::copy(ivec.begin(), ivec.end(), oit);

    return 0;
}