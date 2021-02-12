
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

int main() {
	std::vector<std::vector<std::map<std::string, std::string> > >  vec_vec_map_str_str;
	
	std::map<std::string, std::string> map_str_str_1, map_str_str_2, map_str_str_3, map_str_str_4;
	map_str_str_1["id"]  	= "1";
	map_str_str_1["name"] 	= "Paul";
	map_str_str_1["age"]	= "32";
	map_str_str_1["address"]= "California";
	map_str_str_2["id"]  	= "2";
	map_str_str_2["name"] 	= "Allen";
	map_str_str_2["age"]	= "25";
	map_str_str_2["address"]= "Texas";
	map_str_str_3["id"]		= "3";
	map_str_str_3["name"]	= "Teddy";
	map_str_str_3["age"]	= "23";
	map_str_str_3["address"]= "Norway";
	map_str_str_4["id"]		= "4";
	map_str_str_4["name"]	= "Mark";
	map_str_str_4["age"]	= "25";
	map_str_str_4["address"]= "Rich-Mond";
	std::vector<std::map<std::string, std::string> > vec_map_str_str_1, vec_map_str_str_2;
	vec_map_str_str_1.push_back(map_str_str_1);
	vec_map_str_str_1.push_back(map_str_str_2);
	vec_map_str_str_2.push_back(map_str_str_3);
	vec_map_str_str_2.push_back(map_str_str_4);
	vec_vec_map_str_str.push_back(vec_map_str_str_1);
	// vec_vec_map_str_str.push_back(vec_map_str_str_2);
	
	for (std::vector<std::vector<std::map<std::string, std::string> > >::iterator it = vec_vec_map_str_str.begin(); it != vec_vec_map_str_str.end(); it++) {
		std::cout << "big [" << std::endl;
		for (std::vector<std::map<std::string, std::string> >::iterator itr = (*it).begin(); itr != (*it).end(); itr++) {
			std::cout << std::setw(5) << "sml [" << std::endl;
			for (std::map<std::string, std::string>::iterator iter = (*itr).begin(); iter != (*itr).end(); iter++) {
				std::cout << std::setw(10) << iter->first << " : " << iter->second << std::endl;
			}
			std::cout << std::setw(5) << "]" << std::endl;
		}
		std::cout << "]" << std::endl;
	}
	
	
	return 0;
}