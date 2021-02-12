
#include <stdio.h>

/**
 * 1. 函数对象
 * 2. 强制转换符
 * 3. 类个重载操作符
 */

class Index
{
public:
	int _i;
public:
	Index(int i) : _i(i) {}
	operator int() const;
	
	Index& operator()(int i);
};

Index::operator int() const
{
	return _i;
}

Index& Index::operator()(int i) 
{ 
	_i = i;
	return *this;
}

int main()
{
	Index idx(10);
	
	printf("====> idx = %d\n", (int)idx);
	
	idx(1000);
	printf("====> idx = %d\n", (int)idx);
	
	printf("====> idx = %d\n", (int)idx(1200));
}