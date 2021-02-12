
#include <utility>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>

template<typename K, typename T, typename V>
static void traverse_multi(std::multimap<K, std::pair<T, V> >& multi) {
	for (typename std::multimap<K, std::pair<T, V> >::iterator it = multi.begin(); it != multi.end(); it++) {
		std::cout << std::setw(4) << it->first << " => { " << it->second.first << " : " << it->second.second << " }" << std::endl;
	}
}

int main() {
	std::multimap<int, std::pair<int, int> > multi;
	
	multi.insert(std::make_pair(10, std::pair<int, int>(100, 1000)));
	multi.insert(std::make_pair(20, std::pair<int, int>(200, 2000)));
	multi.insert(std::make_pair(30, std::pair<int, int>(300, 3000)));
	multi.insert(std::make_pair(20, std::pair<int, int>(200, 2000)));
	multi.insert(std::make_pair(40, std::pair<int, int>(400, 4000)));
	
	traverse_multi(multi);

	return 0;
}
