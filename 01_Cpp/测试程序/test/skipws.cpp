#include <iostream>
#include <sstream>
#include <cstring>

// 2019.02.16

int main() {
	std::string istr = "hello world";
	std::string ostr = "not good";
	std::cout << "istr = " << istr << "   ostr = " << ostr << std::endl;
	
	std::stringstream ss, ssi;
	ss << istr;

	std::cout << "ss = " << ss.str() << std::endl;
	
	ss >> ostr;			// 遇到空格，流会读断
	
	std::cout << "istr = " << istr << "   ostr = " << ostr << std::endl;
	
	// 一次流只用一次，重新使用的话最好设置 seekg(0)
	int i = 32, j = 10;
	std::cout << "i = " << i << "  j = " << j << std::endl;
	ssi << i;
	ssi >> j;
	
	std::cout << "i = " << i << "  j = " << j << std::endl;
	
	/////////////////////////////
	
	std::string osstr = "hellohello world";
	std::string isstr = "not good";
	char buf[1024];
	memset(buf, 0, 1024);
	std::ostringstream oss;
	oss << osstr;
	std::cout << "oss = " << oss.str() << std::endl;
	std::istringstream iss(oss.str().c_str());;
	// iss.unsetf(std::ios::skipws);
	// iss >> isstr;
	// iss >> buf;
	iss >> std::noskipws >> buf;
	for (i = 0; i < 16; i++) {		//	遇到空格，流指针会跳到开始位置重新写，原来相应位置的流被覆盖
		iss >> buf[i];
	}
	for (i = 0; i < 16; i++) {
		printf("%02X  ", buf[i]);
	}
	printf("\n");
	
	std::cout << "osstr = " << osstr << "  isstr = " << (std::string)buf << std::endl;
	
	return 0;
}