
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

/**
    可能的实现:
    template<class ForwardIt, class UnaryPredicate, class T>
    void replace_if(ForwardIt first, ForwardIt last,
                    UnaryPredicate p, const T& new_value)
    {
        for (; first != last; ++first) {
            if(p(*first)) {
                *first = new_value;
            }
        }
    }
    
    说明:
        1. 以 new_value 替换范围 [first, last) 中所有匹配谓词的元素。
    
    关键词:
        1. 前向迭代器
        2. 一元谓词，返回值为布尔类型；
        3. 函数返回值: 无    
 */

class Robot
{
public:
    Robot(std::string b) : brand(b) {}
    ~Robot(){}
    std::string brand;
};

struct IsNotFanuc {
    bool operator()(const Robot& r) { return r.brand != "FANUC"; }
};

bool is_not_nachi (const Robot& r) {
    return r.brand != "NACHI";
}

/** 实现约束器 */
bool is_not(const Robot& r, std::string brand) {
    return r.brand != brand;
}

int main()
{
    {
        /** [1] function object */
        std::vector<Robot> Robots;
        Robots.emplace_back("FANUC");
        Robots.emplace_back("NACHI");
        Robots.emplace_back("KUKA");
        Robots.emplace_back("ABB");
                
        std::replace_if(Robots.begin(), Robots.end(),
                        IsNotFanuc(),
                        std::move(Robot("FANUC")));

        for (const auto & ele : Robots) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
    }
    
    {
        /** [2] function pointer */
        std::vector<Robot> Robots;
        Robots.emplace_back("FANUC");
        Robots.emplace_back("NACHI");
        Robots.emplace_back("KUKA");
        Robots.emplace_back("ABB");
                
        std::replace_if(Robots.begin(), Robots.end(),
                        is_not_nachi,
                        std::move(Robot("NACHI")));

        for (const auto & ele : Robots) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
    }
    
    {
        /** [3] constraint */
        std::vector<Robot> Robots;
        Robots.emplace_back("FANUC");
        Robots.emplace_back("NACHI");
        Robots.emplace_back("KUKA");
        Robots.emplace_back("ABB");
                
        std::replace_if(Robots.begin(), Robots.end(),
                        std::bind(is_not, std::placeholders::_1, "KUKA"),
                        std::move(Robot("KUKA")));

        for (const auto & ele : Robots) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
    }
    
    {
        /** [4] lambda expression */
        std::vector<Robot> Robots;
        Robots.emplace_back("FANUC");
        Robots.emplace_back("NACHI");
        Robots.emplace_back("KUKA");
        Robots.emplace_back("ABB");
                
        std::replace_if(Robots.begin(), Robots.end(),
                        [](const Robot& r) {
                            return r.brand != "ABB";
                        },
                        std::move(Robot("ABB")));

        for (const auto & ele : Robots) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
