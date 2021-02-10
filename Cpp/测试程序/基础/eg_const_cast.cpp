
#include <iostream>
#include <string>

void print(char* p)
{
	std::cout << p << std::endl;
}

int main()
{
	std::string str("Hello World");
	
	print(const_cast<char*>(str.c_str()));
	
	return 0;
}