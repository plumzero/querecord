#include <iostream>
#include <string>
#include <vector>

// std::string 里可以有 0 ,但不会显示，但计入 string 的长度

int main() {
	
	int iarr[] = { 65, 66, 0, 67, 68 };
	size_t isize = sizeof(iarr) / sizeof(*iarr);
	
	std::vector<int> ivec;
	
	std::copy(iarr, iarr + isize, std::back_inserter(ivec));
	
	for (auto& ele : ivec) {
		std::cout << ele << "  ";
	}
	std::cout << std::endl;
	
	std::string str(ivec.begin(), ivec.end());
	std::cout << "size: "<< str.size() << "  content:" << str << std::endl;		// 5  ABCD
	
	return 0;
}