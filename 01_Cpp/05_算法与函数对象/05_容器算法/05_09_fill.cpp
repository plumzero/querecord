
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
    可能的实现
    template< class ForwardIt, class T >
    void fill(ForwardIt first, ForwardIt last, const T& value)
    {
        for (; first != last; ++first) {
            *first = value;
        }
    }
    
    说明:
        1. 赋值给定的 value 给 [first, last) 中的元素。
    
    关键词：
        1. 前向迭代器
 */

class Stu
{
public:
    Stu(){}
    ~Stu(){}

    std::string     degree;
};

class Bachelor : public Stu
{
public:
    Bachelor(){ degree = "Bachelor"; }
    ~Bachelor(){}
};

class Master : public Stu
{
public:
    Master(){ degree = "Master"; }
    ~Master(){}
};

class Doctor : public Stu
{
public:
    Doctor(){ degree = "Doctor"; }
    ~Doctor(){}
};

int main()
{
    std::vector<Stu> Students(9);
    
    std::fill(Students.begin(),     Students.begin() + 3, Bachelor());
    std::fill(Students.begin() + 3, Students.begin() + 6, Master());
    std::fill(Students.begin() + 6, Students.end(),       Doctor());
    
    for (const auto & ele : Students) {
        std::cout << ele.degree << std::endl;
    }
    
    return 0;
}