
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class InputIterator, class Function>
      Function for_each(InputIterator first, InputIterator last, Function fn)
    {
      while (first!=last) {
        fn (*first);
        ++first;
      }
      return fn;      // or, since C++11: return move(fn);
    }
    
    关键词:
        1. 输入迭代器
        2. 这里的 fn 不是谓词，返回值类型为任意类型
        3. 返回值类型: 同 fn 返回值
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

/** (写操作)每人加 10 分 */
struct ForEachStu
{
    void operator()(Stu& s) { s._score += 10; }
};

void for_each_stu(Stu& s)
{
    s._score += 10;
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
    for_each(Students.begin(), Students.end(), ForEachStu());
    for (const auto & ele : Students) {
        std::cout << ele._score << " ";
    }
    std::cout << std::endl;
    
    /** [2] function pointer */
    for_each(Students.begin(), Students.end(), for_each_stu);
    for (const auto & ele : Students) {
        std::cout << ele._score << " ";
    }
    std::cout << std::endl;
    
    /** [3] lambda expression */
    for_each(Students.begin(), Students.end(), [](Stu& s) { s._score += 10; });
    for (const auto & ele : Students) {
        std::cout << ele._score << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

