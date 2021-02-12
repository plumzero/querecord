
#include <iostream>
#include <list>

template <typename L>
void traverse_list(std::list<L>& lst) {
	for (typename std::list<L>::iterator it = lst.begin(); it != lst.end(); it++) {
		std::cout << "  " << *it;
	}
	std::cout << std::endl;
}

int main() {
	int ints[] = {75, 23, 65, 42, 13};
	std::list<int> lst(ints, ints + 5);
	
	traverse_list(lst);
	
	return 0;
}