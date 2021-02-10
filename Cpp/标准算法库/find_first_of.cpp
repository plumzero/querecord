
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class InputIt, class ForwardIt, class BinaryPredicate>
    InputIt find_first_of(InputIt first, InputIt last,
                          ForwardIt s_first, ForwardIt s_last,
                          BinaryPredicate p)
    {
        for (; first != last; ++first) {
            for (ForwardIt it = s_first; it != s_last; ++it) {
                if (p(*first, *it)) {
                    return first;
                }
            }
        }
        return last;
    }
    
    关键词:
        1. 前向迭代器
        2. 二元谓词，返回值为布尔类型
        3. 函数返回值: 如果在 [first, last) 中有查找到在 [s_first, s_last) 中出现的任
           何一个元素，则返回指向该元素的首个元素；如果找不到，则返回 last
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

/**
 * 看看给出的动物们(AnimalsSet)有没有生活在非洲(AfricaAnimals)的。
 * 例子有些牵强。
 */
int main()
{   
    std::vector<Animal> AnimalsSet;
    AnimalsSet.emplace_back("Asia",       "Panda");
    AnimalsSet.emplace_back("Europe",     "Tiger");
    AnimalsSet.emplace_back("Antarctica", "Penguin");
    AnimalsSet.emplace_back("Africa",     "Ostrich");
    
    std::vector<Animal> AfricaAnimals;
    AfricaAnimals.emplace_back("Africa", "Lion");
    AfricaAnimals.emplace_back("Africa", "Baboon");
    AfricaAnimals.emplace_back("Africa", "Hippopotamus");
    AfricaAnimals.emplace_back("Africa", "Hyena");
    AfricaAnimals.emplace_back("Africa", "Mongoose");
    
    /** [1] function object */
    auto iterFind = std::find_first_of(AnimalsSet.begin(), AnimalsSet.end(),
                                       AfricaAnimals.begin(), AfricaAnimals.end(),
                                       CompHabitat());
    if (iterFind != AnimalsSet.end()) {
        std::cout << iterFind->name << std::endl;
        AfricaAnimals.emplace_back(iterFind->habitat, iterFind->name);
    } else {
        std::cout << "not found" << std::endl;
    }
    
    /** [2] function pointer */
    iterFind = std::find_first_of(AnimalsSet.begin(), AnimalsSet.end(),
                                  AfricaAnimals.begin(), AfricaAnimals.end(),
                                  comp_habitat);
    if (iterFind != AnimalsSet.end()) {
        std::cout << iterFind->name << std::endl;
        AfricaAnimals.emplace_back(iterFind->habitat, iterFind->name);
    } else {
        std::cout << "not found" << std::endl;
    }
    
    /** [3] lambda expression */
    iterFind = std::find_first_of(AnimalsSet.begin(), AnimalsSet.end(),
                                  AfricaAnimals.begin(), AfricaAnimals.end(),
                                  [](const Animal& a1, const Animal& a2) {
                                    return a1.habitat == a2.habitat;
                                  });
    if (iterFind != AnimalsSet.end()) {
        std::cout << iterFind->name << std::endl;
        AfricaAnimals.emplace_back(iterFind->habitat, iterFind->name);
    } else {
        std::cout << "not found" << std::endl;
    }
    
    
    return 0;
}

