
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现
    template< class InputIt, class UnaryPredicate >
    bool none_of(InputIt first, InputIt last, UnaryPredicate p)
    {
        return std::find_if(first, last, p) == last;
    }
    
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
        1. none_of 语义很拗口，不推荐使用。
        2. 等找到一个好例子时，再替换之。
    
    关键词：
        1. 输入迭代器
        2. 一元谓词，返回值为布尔类型
        3. find_if == last, 一个都没找到，表示不存在满足一元谓词条件的元素
        4. 函数返回值: 如果均不满足谓词条件，才返回 true.
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
    Students.emplace_back(2, 2);
    Students.emplace_back(3, 10);

    bool bl;    
    /** [1] function object */
    bl = std::none_of(Students.begin(), Students.end(), GreatEqualThanAge(18));
    std::cout << std::boolalpha << bl << std::endl;
    
    bl = std::none_of(Students.begin(), Students.end(), GreatEqualThanAge(28));
    std::cout << std::boolalpha << bl << std::endl;
    
    /** [2] function pointer */
    bl = std::none_of(Students.begin(), Students.end(), is_adult);
    std::cout << std::boolalpha << bl << std::endl;
    
    /** [3] lambda expression */
    bl = std::none_of(Students.begin(), Students.end(), [](const Stu& s){ return s.age < 5; });
    std::cout << std::boolalpha << bl << std::endl;
    
    return 0;
}