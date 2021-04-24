#include <iostream>

class Mother
{
public:
    Mother(){ std::cout << "Mother: no parameters" << std::endl; }
    Mother(int a) { std::cout << "Mother: int parameter " << a << std::endl; }
};

class Daughter : public Mother
{
public:
    Daughter(int a) { std::cout << "Daughter: int parameter " << a << std::endl; }
};

class Son : public Mother
{
public:
    Son(int a) : Mother(a) { std::cout << "Son: int parameter " << a << std::endl; }
};

int main()
{
    Daughter kelly(0);
    Son bud(0);
    
    return 0;
}