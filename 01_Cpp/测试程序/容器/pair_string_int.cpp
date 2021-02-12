
#include <utility>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

template<typename T, typename V>
static void traverse_vec_pair(std::vector<std::pair<T, V> >& vec_pair) {
	for (typename std::vector<std::pair<T, V> >::iterator it = vec_pair.begin(); it != vec_pair.end(); it++) {
		std::cout << std::setiosflags(std::ios::left) << std::setw(20) << 
			(*it).first << (*it).second << std::endl;
	}
}

int main() {
	std::pair<std::string, int> pair_string_int;
	pair_string_int = std::make_pair("xiao ming", 928374);
	std::cout << std::setiosflags(std::ios::left) << std::setw(20) << pair_string_int.first << pair_string_int.second << std::endl;
	std::cout << std::endl;
	
	std::vector<std::pair<std::string, int> > vec_pair_string_int;
	
	vec_pair_string_int.push_back(std::pair<std::string, int>("Mercury", 4880));
	vec_pair_string_int.push_back(std::pair<std::string, int>("Venus", 4880));
	vec_pair_string_int.push_back(std::pair<std::string, int>("Earth", 12756));
	vec_pair_string_int.push_back(std::pair<std::string, int>("Mars", 6796));
	vec_pair_string_int.push_back(std::pair<std::string, int>("Jupiter", 142984));
	vec_pair_string_int.push_back(std::pair<std::string, int>("Saturn", 120536));
	vec_pair_string_int.push_back(std::pair<std::string, int>("Uranus", 51118));
	vec_pair_string_int.push_back(std::make_pair("Neptune", 49576));
	
	traverse_vec_pair(vec_pair_string_int);
	std::cout << std::endl;
	
	std::vector<std::pair<int, int> > vec_pair_int_int;
	
	vec_pair_int_int.push_back(std::pair<int, int>(1, 4880));
	vec_pair_int_int.push_back(std::pair<int, int>(2, 4880));
	vec_pair_int_int.push_back(std::pair<int, int>(4, 12756));
	vec_pair_int_int.push_back(std::pair<int, int>(3, 6796));
	vec_pair_int_int.push_back(std::pair<int, int>(8, 142984));
	vec_pair_int_int.push_back(std::pair<int, int>(7, 120536));
	vec_pair_int_int.push_back(std::pair<int, int>(6, 51118));
	vec_pair_int_int.push_back(std::make_pair(5, 49576));
	
	traverse_vec_pair(vec_pair_int_int);
	
	return 0;
}
