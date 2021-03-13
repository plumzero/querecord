
#include <iostream>
#include <vector>
#include <algorithm>

class Stu
{
public:
    Stu(int c, int i, int s) : _class(c), _index(i), _score(s) {}
    ~Stu(){}
    int _class;
    int _index;
    int _score;
    int _time;
};

struct SortStu
{
    bool operator()(const Stu& s1, const Stu& s2) { return s1._score > s2._score; }
};

int main()
{
    {
        std::vector<Stu> Students;
        
        Students.emplace_back(1, 2, 68);
        Students.emplace_back(2, 3, 59);
        Students.emplace_back(2, 1, 68);
        Students.emplace_back(1, 1, 52);
        Students.emplace_back(1, 3, 98);
        Students.emplace_back(1, 4, 34);
        Students.emplace_back(1, 5, 77);
        Students.emplace_back(2, 2, 34);
        Students.emplace_back(2, 4, 68);
        
        std::sort(Students.begin(), Students.end(), SortStu());
        for (const auto & ele : Students) {
            std::cout << " [" << ele._score << ", " << ele._index << "]";
        }
        std::cout << std::endl; 
    }
    
    {
        std::vector<Stu> Students;
        
        Students.emplace_back(1, 2, 68);
        Students.emplace_back(2, 3, 59);
        Students.emplace_back(2, 1, 68);
        Students.emplace_back(1, 1, 52);
        Students.emplace_back(1, 3, 98);
        Students.emplace_back(1, 4, 34);
        Students.emplace_back(1, 5, 77);
        Students.emplace_back(2, 2, 34);
        Students.emplace_back(2, 4, 68);
        
        std::stable_sort(Students.begin(), Students.end(), SortStu());
        for (const auto & ele : Students) {
            std::cout << " [" << ele._score << ", " << ele._index << "]";
        }
        std::cout << std::endl; 
    }
    
    return 0;
}

