#include <iostream>
#include <stdio.h>

class A
{
public:
	void foo() { std::cout << "Common In A" << std::endl; }
};

class B : public A
{
public:
	void foo() { std::cout << "Common In B" << std::endl; }
};

class C : public B
{
public:
	void foo() { std::cout << "Common In C" << std::endl; }
	void fooC() { std::cout << "Only In C" << std::endl; }
};

int main() {
	printf("A::foo() %p\n", &A::foo);
	printf("B::foo() %p\n", &B::foo);
	printf("C::foo() %p\n", &C::foo);

	std::cout << std::endl;
	C* pc = new C;
	pc->foo();
	pc->fooC();

	B* pb = static_cast<B*>(pc);
	pb->foo();	

	A* pa = static_cast<A*>(pc);
	pa->foo();	

	B* pbb = new B;
	pbb->foo();

	A* paa = static_cast<A*>(pbb);
	paa->foo();

	C* pcc = static_cast<C*>(pbb);
	pcc->foo();
	pcc->fooC();

	delete pc;
	delete pbb;

	return 0;
}
