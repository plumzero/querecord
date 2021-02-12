
#include <iostream>

class A{};

class B
{
public:
	explicit B(const A&) {}
	B& operator= (const A& x) { return *this; }
	operator A() { return A(); }
};

void fn(B x) {}

int main()
{
	A foo;
	B bar(foo);
	bar = foo;
	foo = bar;
	
	// fn(foo);		// not allowed for explicit ctor
	fn(bar);
	
	return 0;
}