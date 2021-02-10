

#include <stdio.h>
#include <utility>

class A
{
public:
	int _i;
public:
	A() {}
	A(const A &a) : _i(a._i) { printf("拷贝构造\n"); }
	A(const A &&a) : _i(std::move(a._i)) { printf("移动构造\n"); }
	A(int i) : _i(i) {}
};

int main()
{
	A a1(50);
	
	A a2(a1);
	
	printf("a1._i = %d\n", a1._i);
	printf("a2._i = %d\n", a2._i);
	
	a1._i = 100;
	printf("a1._i = %d\n", a1._i);
	printf("a2._i = %d\n", a2._i);
	
	A a3 = std::move(a1);
	printf("a1._i = %d\n", a1._i);
	printf("a3._i = %d\n", a3._i);

	a1._i = 200;
	printf("a1._i = %d\n", a1._i);
	printf("a3._i = %d\n", a3._i);

	return 0;
}