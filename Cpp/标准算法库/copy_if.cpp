
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

/**
    可能的实现:
    template<class InputIt, class OutputIt, class UnaryPredicate>
    OutputIt copy_if(InputIt first, InputIt last, 
                     OutputIt d_first, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*first))
                *d_first++ = *first;
            ++first;
        }
        return d_first;
    }
    
    说明:
        1. 如果输入迭代器的元素满足谓词，则将其拷贝至输出迭代器中。
    
    关键词:
        1. 输入迭代器 输出迭代器
        2. 一元谓词，返回值为布尔类型
        3. 函数返回值: 返回输出迭代器
 */

class Animal
{
public:
    Animal(std::string h, std::string n) : habitat(h), name(n) {}
    ~Animal(){}
    
    std::string habitat;
    std::string name;
};

struct CompAfrica {
    bool operator()(const Animal& a1) {
        return a1.habitat == "Africa";
    }
};

bool comp_africa(const Animal& a) {
    return a.habitat == "Africa";
}

/**
 * 筛选生活在非洲的动物们。
 */
int main()
{   
    std::vector<Animal> AnimalsSet;
    AnimalsSet.emplace_back("Asia",       "Panda");
    AnimalsSet.emplace_back("Africa",     "Hyena");
    AnimalsSet.emplace_back("Europe",     "Tiger");
    AnimalsSet.emplace_back("Antarctica", "Penguin");
    AnimalsSet.emplace_back("Africa",     "Baboon");
    AnimalsSet.emplace_back("Africa",     "Ostrich");
    
    std::vector<Animal> AfricaAnimals;
    
    /** [1] function object */
    auto iterFind = std::copy_if(AnimalsSet.begin(), AnimalsSet.end(),
                                 std::back_inserter(AfricaAnimals),
                                 CompAfrica());
    for (const auto & ele : AfricaAnimals) {
        std::cout << ele.name << " ";
    }
    std::cout << std::endl;
    
    /** [2] function pointer */
    AfricaAnimals.clear();
    iterFind = std::copy_if(AnimalsSet.begin(), AnimalsSet.end(),
                            std::back_inserter(AfricaAnimals),
                            comp_africa);
    for (const auto & ele : AfricaAnimals) {
        std::cout << ele.name << " ";
    }
    std::cout << std::endl;
    
    /** [3] lambda expression */
    AfricaAnimals.clear();
    iterFind = std::copy_if(AnimalsSet.begin(), AnimalsSet.end(),
                            std::back_inserter(AfricaAnimals),
                            [](const Animal& a) {
                                return a.habitat == "Africa";
                            });
    for (const auto & ele : AfricaAnimals) {
        std::cout << ele.name << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

