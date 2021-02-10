
#include <iostream>

class Mother
{
public:
	Mother(){ std::cout << "Mother: no parameters" << std::endl; }
	Mother(int a) { std::cout << "Mother: int parameter" << std::endl; }
};

class Daughter : public Mother
{
public:
	Daughter(int a) { std::cout << "Daughter: int parameter" << std::endl; }
};

class Son : public Mother
{
public:
	Son(int a) : Mother(a) { std::cout << "Son: int parameter" << std::endl; }
};

int main()
{
	Daughter kelly(0);
	Son bud(0);
	
	return 0;
}