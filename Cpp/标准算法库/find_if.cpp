
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class InputIt, class UnaryPredicate>
    InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        for (; first != last; ++first) {
            if (p(*first)) {
                return first;
            }
        }
        return last;
    }
    
    说明:
        1. 可以看出通过函数对象进行查找更加灵活，函数指针和 lambda 表达式只适用于定
           值查找。
        2. 实际上，函数指针和 lambda 常常用于进行范围的比较。比如说查看 Students 中
           是否有 class == 3 的学生或者 1 < index < 3 的学生，则可以使用函数指针或
           lambda 表达式。
        3. lambda 表达式可以捕获当前环境值或引用，这个比函数对象方便，比函数指针强大。
    
    关键词:
        1. 输入迭代器
        2. 一元谓词，返回值为布尔类型；
        3. 函数返回值: 指向查找对象结果的输入迭代器
 */

class Stu
{
public:
    Stu(int c, int i) : _class(c), _index(i) {}
    ~Stu(){}
    int _class;
    int _index;
};

class CompStu
{
    int _c;
    int _i;
public:
    CompStu(int c, int i) : _c(c), _i(i) {}
    bool operator() (const Stu& stu) { return _c == stu._class && _i == stu._index; }
};

bool comp_stu(const Stu& stu)
{
    return stu._class == 2 && stu._index == 2;
}

int main()
{
    std::vector<Stu> Students;
    
    Students.emplace_back(1, 1);
    Students.emplace_back(1, 2);
    Students.emplace_back(1, 3);
    Students.emplace_back(1, 4);
    Students.emplace_back(1, 5);
    Students.emplace_back(2, 1);
    Students.emplace_back(2, 2);
    Students.emplace_back(2, 3);
    Students.emplace_back(2, 4);

    decltype(Students.begin()) itFind;
    /** [1] function object */
    itFind = std::find_if(Students.begin(), Students.end(), CompStu(1, 2));
    if (itFind != Students.end()) {
        std::cout << "find! " << std::endl;
    } else {
        std::cout << "not find! " << std::endl;
    }
    itFind = std::find_if(Students.begin(), Students.end(), CompStu(2, 8));
    if (itFind != Students.end()) {
        std::cout << "find! " << std::endl;
    } else {
        std::cout << "not find! " << std::endl;
    }
    
    /** [2] function pointer */
    itFind = std::find_if(Students.begin(), Students.end(), comp_stu);
    if (itFind != Students.end()) {
        std::cout << "find! " << std::endl;
    } else {
        std::cout << "not find! " << std::endl;
    }
    
    /** [3] lambda expression */
    itFind = std::find_if(Students.begin(), Students.end(), [](const Stu& stu) {
        return stu._class == 3 && stu._index == 1; });
    if (itFind != Students.end()) {
        std::cout << "find! " << std::endl;
    } else {
        std::cout << "not find! " << std::endl;
    }
        
    return 0;
}