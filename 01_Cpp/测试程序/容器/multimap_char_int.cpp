
#include <iostream>
#include <map>
#include <iomanip>

// 2019.02.17

template <typename K, typename V>
void traverse_map(std::multimap<K, V>& multi, int level = 0) {		// 递归打印，有空再写
	for (typename std::multimap<K, V>::iterator it = multi.begin(); it != multi.end(); it++) {
		std::cout << it->first << " : " << it->second << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	std::multimap<char, int> multi;
	multi.insert(std::pair<char, int>('a', 10));
	multi.insert(std::pair<char, int>('b', 20));
	multi.insert(std::pair<char, int>('b', 150));
	multi.insert(std::make_pair('b', 270));
	multi.insert(std::make_pair('c', 330));
	// multi['c'] = 330;		error multimap 没有定义 []

	traverse_map(multi);
	
	return 0;
}