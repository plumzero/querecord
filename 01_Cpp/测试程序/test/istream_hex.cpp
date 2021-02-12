#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

/**
 *
	将文本文件中的 hex 字符转为 bin 串，文本格式大致如下:
		...
		12 34

		53
		68      09 32

		e9 7e 84 9f
		...
 */

class HexToBin
{
	std::vector<unsigned char> *vec;
public:
	HexToBin(std::vector<unsigned char> *v) : vec(v) { }
	inline void operator() (std::string &s)
	{
		for (auto& ele : s) {
			if (ele >= '0' && ele <= '9') ele -= '0'; else
			if (ele >= 'A' && ele <= 'F') ele -= '7'; else
			if (ele >= 'a' && ele <= 'f') ele -= 'W'; else
				throw -1;
		}
		vec->push_back(static_cast<unsigned char>((s[0] << 4) | s[1]));
	}
};

int main ()
{	
	std::vector<std::string> svec;
	std::vector<unsigned char> ucvec;
	int *pi;
	unsigned char *puc;
	std::ifstream ifs ("ints.txt", std::ios::in | std::ios::binary);
	
	std::copy(std::istream_iterator<std::string>(ifs), 
			  std::istream_iterator<std::string>(), 
			  std::back_inserter(svec));
	
	std::cout << "vector size = " << svec.size() << std::endl;
	
	for (auto& ele : svec) {
		std::cout << ele << "  ";
	}
	std::cout << std::endl << std::endl;
	
	HexToBin tobin(&ucvec);
	std::for_each(svec.begin(), svec.end(), tobin);
	
	std::cout << "vector size = " << ucvec.size() << std::endl;

	puc = reinterpret_cast<unsigned char*>(&ucvec[0]);
	for (size_t i = 0; i < ucvec.size(); i++) {
		printf("%d | ", puc[i]);
	}
	std::cout << std::endl;
	
	ifs.close();
	
	std::ofstream ofs("out.bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
	std::copy(ucvec.begin(), ucvec.end(), std::ostream_iterator<unsigned char>(ofs));
	
	ofs.close();
	
	return 0;
}
