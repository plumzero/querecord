#include <iostream>

class Apple;
class Orange;

class Orange
{
public:
	Orange() {}
	explicit Orange(const Apple& apple) { std::cout << "In orange" << std::endl; }
public:
	void DoSomethingWithOrange(const Orange& orange) {}
};

class Apple
{
public:
	operator Orange () const { std::cout << "In apple" << std::endl; }
};

int main() {
	Apple a;
	Orange oa(a);					// 调用 Orange 中拷贝构造函数
	
	Orange o;
	o.DoSomethingWithOrange(a);		// 调用 Apple 中 Orange 操作符重载

	return 0;
}
