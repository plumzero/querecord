#include <iostream>     // std::cout, std::skipws, std::noskipws
#include <sstream>      // std::istringstream
#include <cstring>

// 2019.02.16
// 解决带有空白符的字符串读入到流再读出流到缓存时，遇到空白符读断的问题
// ss << std::noskipws << buf; 或 ss.setf(std::skipws); 无用

#define BUFSIZE 1024

template <typename itype, typename otype>
static bool convertstr(itype input, otype& output) {
	char ibuf[BUFSIZE], obuf[BUFSIZE];
	size_t i, len;
	std::stringstream ss;
	
	ss << input;
	len = ss.str().length();
	memset(ibuf, 0, BUFSIZE);
	memset(obuf, 0, BUFSIZE);
	std::strcpy(ibuf, ss.str().c_str());
	for (i = 0; i < len && i < BUFSIZE; i++) {
		if (ibuf[i] == 32 || ibuf[i] == 9) {	// 暂时只考虑空格和制表符
			obuf[i] = ibuf[i];
			ss.seekg(i + 1);
		} else {
			ss >> obuf[i];
		}
	}
	if (i == BUFSIZE) {
		obuf[BUFSIZE - 1] = '\0';
	}
	output = obuf;		// 程序有时就是靠蒙的
	
	return true;
}

int main () {

	printf("制表符 %d\n", '	');		// 9
	printf("空格符 %d\n", ' ');		// 32

	char ibuf[1024], obuf[1024];	// 最大字符串处理长度 1024 - 1, 因为处理过程中要用到 C 风格字符串
	size_t i, len;
	std::string iput = "hellohello    world hello	world";
	std::string oput = "cover me";
	std::stringstream ss;
	
	ss << iput;
	len = ss.str().length();
	printf("ss length: %u\n", len);
	if (len > 1023) {
		fprintf(stderr, "too long %d > 1024\n", len);
		return -1;
	}
	
	memset(ibuf, 0, 1024);
	memset(obuf, 0, 1024);
	std::strcpy(ibuf, ss.str().c_str());
	for (i = 0; i < len; i++) {
		if (ibuf[i] == 32 || ibuf[i] == 9) {	// 暂时只考虑空格和制表符
			obuf[i] = ibuf[i];
			ss.seekg(i + 1);
		} else {
			ss >> obuf[i];
		}
		printf("%02X ", obuf[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");
	std::cout << (std::string)obuf << std::endl;
	
	// 模板函数测试
	std::string istr = "good morning";
	std::string ostr = "cover me again";
	std::cout << "istr = " << istr << "  ostr = " << ostr << std::endl;
	
	if (true == convertstr(istr, ostr)) {
		std::cout << "istr = " << istr << "  ostr = " << ostr << std::endl;
	} else {
		printf("failed\n");
	}
	
	
	return 0;
}