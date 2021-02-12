
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

template <typename T>
static void traverse_vec(std::vector<T>& vec) {
	for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); it++) {
		std::cout << std::setw(4) << "" << std::setiosflags(std::ios::left) << std::setw(10) << *it << std::endl;
	}
}

int main() {
	std::string str("red orange yellow green cyan blue purple");
	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		std::cout << std::setw(4) << *it << std::endl;;
	}

	std::vector<std::string> vec_str;
	vec_str.push_back("light red");
	vec_str.push_back("orange");
	vec_str.push_back("egg yellow");
	vec_str.push_back("green");
	vec_str.push_back("cyan");
	vec_str.push_back("deep blue");
	vec_str.push_back("purple");
	
	traverse_vec(vec_str);
	
	return 0;
}

数据驱动 ：在 Unity 的 ScriptObject 中明显就是数据驱动，其核心思想就是改动数据而不必改动代码。而当你要使用数据驱动时候一定要分清楚什么可以硬编码什么可以数据驱动，配置太多的话是很影响开发效率和可阅读性。
降低指针跳转消耗 ：我觉得这个也是 ECS 提出的原因之一，在大型游戏中面对的是巨量的游戏物体，这个时候游戏物体中又有各种指针跳转的话造成的性能消耗就不能忽视了。所以在写代码时候要注意降低指针跳转，尽量让内存连续分布，比如使用结构体和数组。当然内存连续分布也可以减少内存碎片。
