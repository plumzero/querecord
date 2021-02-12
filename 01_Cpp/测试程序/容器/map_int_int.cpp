#include <iostream>
#include <iomanip>
#include <map>

int main() {
	std::map<int, int> map_int_int;
	
	map_int_int[10] = 11;
	map_int_int[20] = 21;
	map_int_int[30] = 31;
	
	for (std::map<int, int>::iterator it = map_int_int.begin(); it != map_int_int.end(); it++) {
		std::cout << it->first << " : " << it->second << std::endl;
	}
	
	std::map<int, std::map<int, int> > map_int_map_int_int;
	std::map<int, int> map_int_int_help1, map_int_int_help2; 
	map_int_int_help1[2] = 3;
	map_int_int_help1[3] = 4;
	map_int_int_help1[4] = 5;
	map_int_int_help2[12] = 13;
	map_int_int_help2[13] = 14;
	map_int_int_help2[14] = 15;
	map_int_map_int_int[1] = map_int_int_help1;
	map_int_map_int_int[11] = map_int_int_help2;
	for (std::map<int, std::map<int, int> >::iterator it = map_int_map_int_int.begin(); it != map_int_map_int_int.end(); it++) {
		std::cout << it->first << " : {" << std::endl;
		for (std::map<int, int>::iterator itr = it->second.begin(); itr != it->second.end(); itr++) {
			std::cout << std::setw(5) << itr->first << " : " << itr->second << std::endl;
		}
		std::cout << "}" << std::endl;
	}
	// std::setiosflags(std::ios::right);
	std::cout << std::setw(10) << "i = " << 10 <<std::endl;
	std::cout << std::setw(10) << "hahaha = " << 10000000 <<std::endl;
	std::cout << "i = " << std::setw(10) << 10 <<std::endl;
	std::cout << "hahaha = " << std::setw(10) << 10000000 <<std::endl;
	
	
	return 0;
}