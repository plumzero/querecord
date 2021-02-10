
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现
    template< class InputIt, class UnaryPredicate >
    bool all_of(InputIt first, InputIt last, UnaryPredicate p)
    {
        return std::find_if_not(first, last, p) == last;
    }
    
    template<class InputIt, class UnaryPredicate>
    InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q)
    {
        for (; first != last; ++first) {
            if (!q(*first)) {
                return first;
            }
        }
        return last;
    }
    
    关键词：
        1. 输入迭代器
        2. 一元谓词，返回值为布尔类型
        3. find_if_not == last, 表示元素均满足一元谓词条件
        4. 函数返回值: 如果均满足谓词条件，才会返回 true
 */

class Stu
{
public:
    Stu(int i, int a) : index(i), age(a) {}
    ~Stu(){}
    
    int index;
    int age;
};

struct GreatEqualThanAge
{
    bool operator()(const Stu& s) { return s.age >= age; }
    GreatEqualThanAge(int a) : age(a) {}
private:
    int age;
};

bool is_adult(const Stu& s)
{
    return s.age >= 18;
}

int main()
{
    std::vector<Stu> Students;
    Students.emplace_back(1, 19);
    Students.emplace_back(2, 30);
    Students.emplace_back(3, 19);
    Students.emplace_back(4, 20);
    Students.emplace_back(5, 25);
    Students.emplace_back(6, 32);
    Students.emplace_back(7, 18);
    bool bl;
    
    /** [1] function object */
    bl = std::all_of(Students.begin(), Students.end(), GreatEqualThanAge(18));
    std::cout << std::boolalpha << bl << std::endl;
    
    bl = std::all_of(Students.begin(), Students.end(), GreatEqualThanAge(28));
    std::cout << std::boolalpha << bl << std::endl;
    
    /** [2] function pointer */
    bl = std::all_of(Students.begin(), Students.end(), is_adult);
    std::cout << std::boolalpha << bl << std::endl;
    
    /** [3] lambda expression */
    bl = std::all_of(Students.begin(), Students.end(), [](const Stu& s){ return s.age >= 18; });
    std::cout << std::boolalpha << bl << std::endl;
    
    return 0;
}