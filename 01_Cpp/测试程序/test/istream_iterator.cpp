#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>

int main ()
{
	{
		std::cout << "===== vector 测试 =====" << std::endl;
		
		std::vector<int> ivec;
		std::vector<unsigned char> ucvec;
		int *pi;
		unsigned char *puc;
		std::ifstream ifs ("ints.txt", std::ios::in | std::ios::binary);
		
		std::copy(std::istream_iterator<int>(ifs), std::istream_iterator<int>(), std::back_inserter(ivec));
		std::cout << "vector size = " << ivec.size() << std::endl;
		
		for (auto& ele : ivec) {
			std::cout << ele << "  ";
		}
		std::cout << std::endl;
				
		pi = reinterpret_cast<int*>(&ivec[0]);
		for (size_t i = 0; i < ivec.size(); i++) {
			printf("%d | ", pi[i]);
		}
		std::cout << std::endl;
		
		// unsigned char 与 int 内存分配模型不一致，需要重新定义 vector 存入
		std::copy(ivec.begin(), ivec.end(), std::back_inserter(ucvec));
		
		/** 
			内存分配模型不一致，一个 int 占 4 个字节，一个 char 类型占一个字节
		 */
		// puc = reinterpret_cast<int*>(pi);		// error
		puc = reinterpret_cast<unsigned char*>(&ucvec[0]);
		for (size_t i = 0; i < ucvec.size(); i++) {
			printf("%d | ", puc[i]);
		}
		std::cout << std::endl;
		
		ifs.close();
	}
	
	return 0;
}