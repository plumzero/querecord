
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class ForwardIt, class BinaryPredicate>
    ForwardIt adjacent_find(ForwardIt first, ForwardIt last, 
                            BinaryPredicate p)
    {
        if (first == last) {
            return last;
        }
        ForwardIt next = first;
        ++next;
        for (; next != last; ++next, ++first) {
            if (p(*first, *next)) {
                return first;
            }
        }
        return last;
    }
    
    说明:
        1. 寻找两个相继的等同元素
    
    关键词:
        1. 前向迭代器
        2. 二元谓词，返回值为布尔类型
        3. 函数返回值: 返回指向首对等同元素的首个元素的迭代器。
 */

class Animal
{
public:
    Animal(std::string h, std::string n) : habitat(h), name(n) {}
    ~Animal(){}
    
    std::string habitat;
    std::string name;
};

struct CompHabitat {
    bool operator()(const Animal& a1, const Animal& a2) {
        return a1.habitat == a2.habitat;
    }
};

bool comp_habitat(const Animal& a1, const Animal& a2)
{
    return a1.habitat == a2.habitat;
}

int main()
{   
    std::vector<Animal> AnimalsSet;
    AnimalsSet.emplace_back("Asia",       "Panda");
    AnimalsSet.emplace_back("Europe",     "Tiger");
    AnimalsSet.emplace_back("Africa",     "Ostrich");
    AnimalsSet.emplace_back("Africa",     "Lion");
    AnimalsSet.emplace_back("Africa",     "Hyena");
    AnimalsSet.emplace_back("Antarctica", "Penguin");
    AnimalsSet.emplace_back("Africa",     "Baboon");
    AnimalsSet.emplace_back("Africa",     "Hippopotamus");
        
    /** [1] function object */
    auto iterFind = std::adjacent_find(AnimalsSet.begin(), AnimalsSet.end(), CompHabitat());
    if (iterFind != AnimalsSet.end()) {
        std::cout << iterFind->name << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    
    /** [2] function pointer */
    iterFind = std::adjacent_find(AnimalsSet.begin(), AnimalsSet.end(), comp_habitat);
    if (iterFind != AnimalsSet.end()) {
        std::cout << iterFind->name << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    
    /** [3] lambda expression */
    iterFind = std::adjacent_find(AnimalsSet.begin(), AnimalsSet.end(), 
                                  [](const Animal& a1, const Animal& a2) {
                                    return a1.habitat == a2.habitat;
                                  });
    if (iterFind != AnimalsSet.end()) {
        std::cout << iterFind->name << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    
    return 0;
}

