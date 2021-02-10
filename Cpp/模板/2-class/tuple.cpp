
#include <iostream>
#include <tuple>
#include <vector>
#include <string>

int main()
{
    std::vector<std::tuple<std::string, int>> listens;
        
    listens.emplace_back(std::make_tuple("192.168.1.11", 8080));
    listens.emplace_back(std::make_tuple("192.168.10.37", 1234));
    
    for (const auto & ele : listens) {
        std::cout << std::get<0>(ele) << " : " << std::get<1>(ele) << std::endl;
    }
    
    return 0;
}