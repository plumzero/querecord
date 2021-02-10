
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

/**
    可能的实现:
    template<class InputIt, class OutputIt, 
             class UnaryPredicate, class T>
    OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first,
                             UnaryPredicate p, const T& new_value)
    {
        for (; first != last; ++first) {
            *d_first++ = p( *first ) ? new_value : *first;
        }
        return d_first;
    }
    
    说明:
        1. 复制来自范围 [first, last) 的所有元素到始于 d_first 的范围，并以
            new_value 替换所有满足特定判别标准的元素。
        2. 源与目标范围不能重叠。
    
    关键词:
        1. 输入迭代器 输出迭代器
        2. 一元谓词，返回值为布尔类型；
        3. 函数返回值: 输出迭代器
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

int main()
{
    {
        /** [1] function object */
        std::vector<Robot> Robots;
        Robots.emplace_back("FANUC");
        Robots.emplace_back("NACHI");
        Robots.emplace_back("KUKA");
        Robots.emplace_back("ABB");
                
        std::vector<Robot> RobotsCopy;
        std::replace_copy_if(Robots.begin(), Robots.end(),
                             std::back_inserter(RobotsCopy),
                             IsNotFanuc(),
                             std::move(Robot("FANUC")));

        for (const auto & ele : Robots) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
        for (const auto & ele : RobotsCopy) {
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
        
        std::vector<Robot> RobotsCopy;
        std::replace_copy_if(Robots.begin(), Robots.end(),
                             std::back_inserter(RobotsCopy),
                             is_not_nachi,
                             std::move(Robot("NACHI")));

        for (const auto & ele : Robots) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
        for (const auto & ele : RobotsCopy) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
    }
    
    {
        /** [3] lambda expression */
        std::vector<Robot> Robots;
        Robots.emplace_back("FANUC");
        Robots.emplace_back("NACHI");
        Robots.emplace_back("KUKA");
        Robots.emplace_back("ABB");
        
        std::vector<Robot> RobotsCopy;        
        std::replace_copy_if(Robots.begin(), Robots.end(),
                             std::back_inserter(RobotsCopy),
                             [](const Robot& r) {
                                return r.brand != "ABB";
                             },
                             std::move(Robot("ABB")));

        for (const auto & ele : Robots) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
        for (const auto & ele : RobotsCopy) {
            std::cout << ele.brand << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
