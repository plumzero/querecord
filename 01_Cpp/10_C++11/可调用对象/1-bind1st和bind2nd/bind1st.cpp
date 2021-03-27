
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

/** 注意: 请先从 bind2nd 的实现开始看起 */

class Stu
{
public:
    Stu(int i, int s) : index(i), score(s) {}
    ~Stu(){}
    int index;
    int score;
};

/** (1) 与 bind2nd 相比，二元函数传参颠倒了一下 */
Stu& add_score(int score, Stu& s)
{
    s.score += score;
    return s;
}

int main()
{
    {
        /** [1] 测试: 每个学习加 11 分 */
        std::vector<Stu> Students;
        
        Students.emplace_back(1, 11);
        Students.emplace_back(2, 22);
        Students.emplace_back(3, 33);
        Students.emplace_back(4, 44);
        Students.emplace_back(5, 55);
        Students.emplace_back(6, 66);
                
        std::transform(Students.begin(), Students.end(), Students.begin(),
                       std::bind(add_score, 11, std::placeholders::_1));    /** (2) 绑定也颠倒了一下 */
        
        /**
         * (3) 所以，对第一参绑定还是第二参绑定，取决于程序员实现二元函数对象的方式。
         *     一般地，会对第二参变量进行绑定。bind1st 是不常用的。
         */
        
        for (const auto & ele : Students) {
            std::cout << "[index, score] = " << ele.index << ", " << ele.score << std::endl;
        }
    }
    
    return 0;
}
