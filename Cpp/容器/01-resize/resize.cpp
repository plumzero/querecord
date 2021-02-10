
#include <iostream>
#include <vector>
#include <algorithm>

class Stu
{
public:
    Stu(){}     /** 如果将该行注释，程序在编译时会因找不到缺省构造函数而报错，因为 resize
                    对容器尺寸进行了调整，这时要 value-initialized */
    Stu(int c, int i) : _class(c), _index(i) {}
    ~Stu(){}
    int _class;
    int _index;
};

int main()
{
    std::vector<Stu> Students;
    
    Students.emplace_back(1, 1);
    Students.emplace_back(1, 2);
    Students.emplace_back(1, 3);
    Students.emplace_back(2, 1);
    Students.emplace_back(2, 2);
    Students.emplace_back(2, 3);

    auto itEnd = std::remove_if(Students.begin(), Students.end(), [](const Stu& stu) {
        return stu._class == 1 && stu._index == 1; });
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