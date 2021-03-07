
#include <iostream>
#include <map>

int main()
{
    // 通过键删除元素
    {
        std::map<std::string, size_t> people {
            { "Fred", 45 },
            { "Joan", 33 },
            { "Jill", 22 }
        };
        
        std::string name{"Joan"};
        
        if (people.erase(name) == 1) {
            std::cout << name << " was removed." << std::endl;
        } else {
            std::cout <<name << " was not found." << std::endl;
        }   
    }
    
    // 通过迭代器删除元素
    {
        std::map<std::string, size_t> people {
            { "Fred", 45 },
            { "Joan", 33 },
            { "Jill", 22 }
        };
        
        auto iter = people.erase(std::begin(people));
        if (iter == std::end(people)) {
            std::cout << "The last element was removed." << std::endl;
        } else {
            std::cout << "The element preceding " << iter->first << " was removed." << std::endl;
        }
    }
    
    // 移除两个迭代器之间的元素
    {
        std::map<std::string, size_t> people {
            { "Fred", 45 },
            { "Joan", 33 },
            { "Jill", 22 }
        };
        
        auto iter = people.erase(++std::begin(people), --std::end(people));
        
        std::cout << "The element preceding " << iter->first << " was removed." << std::endl;
    }
    
    return 0;
}