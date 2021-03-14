
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class ForwardIt, class UnaryPredicate>
    ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
    {
        first = std::find_if(first, last, p);
        if (first != last)
            for(ForwardIt i = first; ++i != last; )
                if (!p(*i))
                    *first++ = std::move(*i);
        return first;
    }
    
    说明:
        1. 从 [first, last) 中移除匹配谓词的元素
    
    关键词:
        1. 前向迭代器
        2. 一元谓词，返回值为布尔类型；
        3. 函数返回值: 如果有元素被移除，则指向新值范围的尾后迭代器；如果没
           有元素被移除，它指向未定值(位于此迭代器与 end 之间的任何迭代器)
    
    注意:
        1. 源内操作。后续元素会移动到被移除元素的位置，原来的 end() 迭代器会失效。
 */

class Stu
{
public:
    Stu(){}
    Stu(int c, int i) : _class(c), _index(i) {}
    ~Stu(){}
    int _class;
    int _index;
};

struct RemoveStu
{
    RemoveStu(int c, int i) : _c(c), _i(i) {}
    bool operator()(const Stu& s) { return s._class == _c && s._index == _i; }
private:
    int _c;
    int _i;
};

bool remove_stu(const Stu& stu)
{
    return stu._class == 2 && stu._index == 3;
}

int main()
{
    std::vector<Stu> Students;
    
    Students.emplace_back(1, 1);
    Students.emplace_back(1, 2);
    Students.emplace_back(1, 3);
    Students.emplace_back(2, 1);
    Students.emplace_back(2, 2);
    Students.emplace_back(2, 3);

    /** [1] function object */
    auto itEnd = std::remove_if(Students.begin(), Students.end(), RemoveStu(1, 2));
    if (itEnd != Students.end()) {
        std::cout << "remove success" << std::endl;
        Students.resize(5);
    } else {
        std::cout << "not exist" << std::endl;
    }
    
    itEnd = std::remove_if(Students.begin(), Students.end(), RemoveStu(2, 8));
    if (itEnd != Students.end()) {
        std::cout << "remove success" << std::endl;
        Students.resize(itEnd - Students.begin());
    } else {
        std::cout << "not exist" << std::endl;
    }
    
    /** [2] function pointer */
    itEnd = std::remove_if(Students.begin(), Students.end(), remove_stu);
    if (itEnd != Students.end()) {
        std::cout << "remove success" << std::endl;
        Students.resize(itEnd - Students.begin());
    } else {
        std::cout << "not exist" << std::endl;
    }

    /** [3] lambda expression */
    itEnd = std::remove_if(Students.begin(), Students.end(), [](const Stu& stu) {
        return stu._class == 3 && stu._index == 1; });
    if (itEnd != Students.end()) {
        std::cout << "remove success" << std::endl;
        Students.resize(itEnd - Students.begin());
    } else {
        std::cout << "not exist" << std::endl;
    }
        
    for (const auto & ele : Students) {
        std::cout << "[class:index] = " << ele._class << " : " << ele._index << std::endl;
    }

    return 0;
}