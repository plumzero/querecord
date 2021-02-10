
#include <vector>
#include <iostream>

struct A
{
    int x;
    double y;
    A(int a, double b): x(a), y(b) {}
};

int main()
{
    std::vector<A> v;
    v.emplace_back(1, 2);
    std::cout << v.size() << std::endl;
    
    return 0;
}