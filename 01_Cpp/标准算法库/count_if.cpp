
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class InputIt, class UnaryPredicate>
    typename iterator_traits<InputIt>::difference_type
        count_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        typename iterator_traits<InputIt>::difference_type ret = 0;
        for (; first != last; ++first) {
            if (p(*first)) {
                ret++;
            }
        }
        return ret;
    }
    
    关键词:
        1. 输入迭代器
        2. 一元谓词，返回值为布尔类型
        3. 函数返回值: 满足一元谓词条件的元素数量。
 */
 
class Stu
{
public:
    Stu(int i, int a) : index(i), age(a) {}
    ~Stu(){}
    
    int index;
    int age;
};

struct AgeGroupComp
{
    bool operator()(const Stu& s) { return l <= s.age && s.age < r; }
    AgeGroupComp(int left, int right) : l(left), r(right) {} 
private:
    int l;
    int r;
};

bool greater_than_ten(const Stu& s)
{
    return s.age > 10;
}

int main()
{
    std::vector<Stu> Students;
    Students.emplace_back(1, 15);
    Students.emplace_back(2, 12);
    Students.emplace_back(3, 10);
    Students.emplace_back(4, 14);
    Students.emplace_back(5, 16);
    Students.emplace_back(6, 9);
    Students.emplace_back(7, 11);
    Students.emplace_back(8, 13);

    int ret;
    /** [1] function object */
    ret = std::count_if(Students.begin(), Students.end(), AgeGroupComp(10, 15));
    std::cout << ret << std::endl;
    
    /** [2] function pointer */
    ret = std::count_if(Students.begin(), Students.end(), greater_than_ten);
    std::cout << ret << std::endl;
    
    /** [3] lambda expression */
    ret = std::count_if(Students.begin(), Students.end(), [](const Stu& s){ return s.age <= 10; });
    std::cout << ret << std::endl;

}