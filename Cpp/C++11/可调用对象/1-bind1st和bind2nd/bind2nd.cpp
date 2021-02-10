
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Stu
{
public:
    Stu(int i, int s) : index(i), score(s) {}
    ~Stu(){}
    int index;
    int score;
};

Stu& add_score(Stu& s, int score)
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
                       std::bind(add_score, std::placeholders::_1, 11));
        
        for (const auto & ele : Students) {
            std::cout << "[index, score] = " << ele.index << ", " << ele.score << std::endl;
        }
    }
    
    return 0;
}
