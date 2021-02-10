#include <sstream>
#include <iostream>
#include <cstring>

int main() {
	std::stringstream ss, ssget;
	char buf[32] = { 0 };

	ss << "hello world";
	ss >> buf;
	std::cout << buf << std::endl;
	
	memset(buf, 0, 32);

	ssget << "hello world	tab symbol";
	ssget.get(buf, 32);	// second para at least equal to string_len + 1 ('\0')
	
	std::cout << buf << std::endl;

	return 0;
}
