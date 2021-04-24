
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现:
        暂未没找到。但官方说是一个二元表达式(BinaryPredicate)
        适用的迭代器类型为随机访问迭代器。
    
    关键词:
        1. 随机访问迭代器(官方说法)
        2. 二元谓词
        3. 无函数返回值
 */

class Stu
{
public:
    Stu(int c, int i, int s) : _class(c), _index(i), _score(s) {}
    ~Stu(){}
    int _class;
    int _index;
    int _score;
};

struct SortStu
{
    bool operator()(const Stu& s1, const Stu& s2) { return s1._score > s2._score; }
};

bool sort_stu(const Stu& s1, const Stu& s2)
{
    return s1._score > s2._score;
}

int main()
{
    std::vector<Stu> Students;
    
    Students.emplace_back(1, 1, 52);
    Students.emplace_back(1, 2, 68);
    Students.emplace_back(1, 3, 98);
    Students.emplace_back(1, 4, 34);
    Students.emplace_back(1, 5, 77);
    Students.emplace_back(2, 1, 25);
    Students.emplace_back(2, 2, 34);
    Students.emplace_back(2, 3, 59);
    Students.emplace_back(2, 4, 20);
    
    /** [1] function object */
    std::cout << "使用 function object 排序前: " << std::endl;
    for (const auto & ele : Students) {
        std::cout << " [" << ele._score << ", " << ele._index << "]";
    }
    std::cout << std::endl;
    std::cout << "使用 function object 排序后: " << std::endl;
    std::sort(Students.begin(), Students.end(), SortStu());
    for (const auto & ele : Students) {
        std::cout << " [" << ele._score << ", " << ele._index << "]";
    }
    std::cout << std::endl;
    
    /** [2] function pointer */
    random_shuffle(Students.begin(), Students.end());
    std::cout << "使用 function pointer 排序前: " << std::endl;
    for (const auto & ele : Students) {
        std::cout << " [" << ele._score << ", " << ele._index << "]";
    }
    std::cout << std::endl;
    std::cout << "使用 function pointer 排序后: " << std::endl;
    std::sort(Students.begin(), Students.end(), sort_stu);
    for (const auto & ele : Students) {
        std::cout << " [" << ele._score << ", " << ele._index << "]";
    }
    std::cout << std::endl;
    
    /** [3] lambda expression */
    random_shuffle(Students.begin(), Students.end());
    std::cout << "使用 lambda expression 排序前: " << std::endl;
    for (const auto & ele : Students) {
        std::cout << " [" << ele._score << ", " << ele._index << "]";
    }
    std::cout << std::endl;
    std::cout << "使用 lambda expression 排序后: " << std::endl;
    std::sort(Students.begin(), Students.end(), [](const Stu& s1, const Stu& s2) {
        return s1._score > s2._score;
    });
    for (const auto & ele : Students) {
        std::cout << " [" << ele._score << ", " << ele._index << "]";
    }
    std::cout << std::endl;
    
    return 0;
}

