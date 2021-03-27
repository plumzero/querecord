
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/**
    可能的实现:
    template<class InputIt, class OutputIt, class UnaryPredicate>
    OutputIt remove_copy_if(InputIt first, InputIt last,
                            OutputIt d_first, UnaryPredicate p)
    {
        for (; first != last; ++first) {
            if (!p(*first)) {
                *d_first++ = *first;
            }
        }
        return d_first;
    }
    
    说明:
        1. 操作结果与下列操作方法的操作结果等同:
           源容器拷贝为一个目标容器，在目标容器中剔除匹配谓词的元素。返回结果为指向
           目标容器的输出迭代器。       
        2. 源外操作。迭代器不会失效
    
    关键词:
        1. 输入迭代器 输出迭代器
        2. 一元谓词，返回值为布尔类型；
        3. 函数返回值: 输出迭代器
    
    注意:
        1. 源与目标不能重叠。
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
    {
        std::vector<Stu> Students;
        
        Students.emplace_back(1, 1);
        Students.emplace_back(1, 2);
        Students.emplace_back(1, 3);
        Students.emplace_back(2, 1);
        Students.emplace_back(2, 2);
        Students.emplace_back(2, 3);

        std::vector<Stu> RemStudents;
        /** [1] function object */
        std::remove_copy_if(Students.begin(), Students.end(),
                            std::back_inserter(RemStudents),
                            RemoveStu(1, 2));

        std::cout << "源:" << std::endl;
        for (const auto & ele : Students) {
            std::cout << "[class:index] = " << ele._class << " : " << ele._index << std::endl;
        }
        
        std::cout << "拷贝删除式容器:" << std::endl;
        for (const auto & ele : RemStudents) {
            std::cout << "[class:index] = " << ele._class << " : " << ele._index << std::endl;
        }
    }
    
    {
        std::vector<Stu> Students;
        
        Students.emplace_back(1, 1);
        Students.emplace_back(1, 2);
        Students.emplace_back(1, 3);
        Students.emplace_back(2, 1);
        Students.emplace_back(2, 2);
        Students.emplace_back(2, 3);

        std::vector<Stu> RemStudents;
        /** [2] function pointer */
        std::remove_copy_if(Students.begin(), Students.end(), std::back_inserter(RemStudents), remove_stu);
        std::cout << "源:" << std::endl;
        for (const auto & ele : Students) {
            std::cout << "[class:index] = " << ele._class << " : " << ele._index << std::endl;
        }
        
        std::cout << "拷贝删除式容器:" << std::endl;
        for (const auto & ele : RemStudents) {
            std::cout << "[class:index] = " << ele._class << " : " << ele._index << std::endl;
        }
    }
    
    {
        std::vector<Stu> Students;
        
        Students.emplace_back(1, 1);
        Students.emplace_back(1, 2);
        Students.emplace_back(1, 3);
        Students.emplace_back(2, 1);
        Students.emplace_back(2, 2);
        Students.emplace_back(2, 3);

        std::vector<Stu> RemStudents;
        /** [3] lambda expression */
        std::remove_copy_if(Students.begin(), Students.end(), 
                            std::back_inserter(RemStudents),
                            [](const Stu& stu) {
            return stu._class == 3 && stu._index == 1; });

        std::cout << "源:" << std::endl;
        for (const auto & ele : Students) {
            std::cout << "[class:index] = " << ele._class << " : " << ele._index << std::endl;
        }
        
        std::cout << "拷贝删除式容器:" << std::endl;
        for (const auto & ele : RemStudents) {
            std::cout << "[class:index] = " << ele._class << " : " << ele._index << std::endl;
        }
    }

    return 0;
}