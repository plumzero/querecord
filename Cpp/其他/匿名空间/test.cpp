
#include <iostream>

namespace {
    void print()
    {
        std::cout << "in anonymous space" << std::endl;
    }
};

void print()
{
    std::cout << "not in anonymous space" << std::endl;
}

int main()
{
    ::print();

    return 0;
}