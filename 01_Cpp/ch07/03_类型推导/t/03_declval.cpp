
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

struct A {
    virtual int value() = 0;
};

class B {
    int val;
public:
    B(){}
    B(int i, int j): val(i*j){}
    int value(){ return val; }
};

struct NonDefault
{
    NonDefault() = delete;
    int foo() const { return 1; }
};

class Stu
{
public:
    Stu(int i, int mi, int ma) : index(i), min(mi), max(ma) {}
    ~Stu(){}
    int index;
    int min;
    int max;
};

struct EqualRangeStu
{
    bool operator()(const Stu &s, const int droppoint) {
        return s.max < droppoint;
    }
    bool operator()(const int droppoint, const Stu &s) {
        return droppoint < s.min;
    }
};

struct SortStu
{
    bool operator()(const Stu& s1, const Stu& s2) { 
        return s1.min < s2.min || (s1.min == s2.min && s1.max < s2.max); 
    }
};

int main()
{
    {
        /** [1] 示例一: 抽象类 */
        decltype(std::declval<A>().value()) a;      // int a
        decltype(std::declval<B>().value()) b;      // int b
        decltype(B(0, 0).value()) c;                // int c
    }
    
    {
        /** [2] 示例二: 缺省构造函数被禁用，无法创建对象 */
        //  decltype(NonDefault().foo()) n1;            // 错误：无默认构造函数
        decltype(std::declval<NonDefault>().foo()) n2;  // int n2
    }
    
    {
        /** [3] 示例三:  */
        std::vector<Stu> Students;
        Students.emplace_back(3, 3, 5); // pass
        Students.emplace_back(2, 2, 9); // pass
        Students.emplace_back(1, 3, 5); // pass
        Students.emplace_back(4, 1, 2); // not pass
        Students.emplace_back(5, 4, 7); // not pass
        Students.emplace_back(6, 1, 9); // pass
        Students.emplace_back(7, 6, 9); // not pass
        Students.emplace_back(8, 1, 1); // not pass
        
        decltype(std::equal_range(Students.begin(), Students.end(), std::declval<Stu>())) pairIter;
        decltype(pairIter.first) iter;
        /**
         * 关于 pairIter, 也可以这样定义，不过看起来效果不如上面的好。
         *  decltype(std::equal_range(Students.begin(), Students.end(), Stu(0, 0, 0))) pairIter;
         */
        
        std::sort(Students.begin(), Students.end(), SortStu());
        std::cout << "排序后:" << std::endl;
        for_each(Students.begin(), Students.end(), [](const Stu& s) {
            std::cout << "[index, min, max] = " << s.index << " " << s.min << " " << s.max << std::endl;
        });
        
        pairIter = std::equal_range(Students.begin(), Students.end(), 3, EqualRangeStu());
        if (pairIter.first != Students.end() && pairIter.first != pairIter.second) {
            std::cout << pairIter.second - pairIter.first << " member(s) satified" << std::endl;
            for (iter = pairIter.first; iter != pairIter.second; iter++) {
                std::cout << "[index, min, max] = " << iter->index << " " << iter->min << " " 
                          << iter->max << std::endl;
            }
        } else {
            std::cout << "no member satified" << std::endl; 
        }
    }
    
    return 0;
}
