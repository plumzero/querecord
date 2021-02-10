
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class ForwardIt, class T, class Compare>
    std::pair<ForwardIt,ForwardIt> 
        equal_range(ForwardIt first, ForwardIt last,
                    const T& value, Compare comp);
    {
        return std::make_pair(std::lower_bound(first, last, value, comp),
                              std::upper_bound(first, last, value, comp));
    }
    说明:
        1. 如果元素与 value 比较后满足条件 (!comp(a,b) && !comp(b,a)) 为 true, 则该元素
           满足条件。
        2. 返回的 pair 第一个成员指向满足条件的第一个元素，第二个成员指向满足条件的最后
           一个成员的下一个元素。
        3. std::equal_range 可以看作是 std::lower_bound 和 std::upper_bound 的结合使用；
        
    关键词:
        1. 前向迭代器。这说明为使返回的结果准确，必须要保证要比较的元素应该是按某个成员
           有序的。具体哪个成员根据实际情况而定。
        2. 二元谓词(首参数是 ForwardIt, 第二个参数是 value)
    注意:
        1. 总而言之，言而总之， equal_range 的使用场景比较苛刻，容器在调用这个函数之前，
           必须要保证元素的成员有序。
 */

class Stu
{
public:
    Stu(int i, int mi, int ma) : index(i), min(mi), max(ma) {}
    ~Stu(){}
    int index;
    int min;
    int max;
};

struct EqualRangeStu
{
    bool operator()(const Stu &s, const int droppoint) {
        return s.max < droppoint;
    }
    bool operator()(const int droppoint, const Stu &s) {
        return droppoint < s.min;
    }
};

struct SortStu
{
    bool operator()(const Stu& s1, const Stu& s2) { 
        return s1.min < s2.min || (s1.min == s2.min && s1.max < s2.max); 
    }
};

int main()
{
    /** 判断每个元素是否满足 min <= 3 <= max*/

    {
        /** 元素成员无序，结果不准确 */
        std::vector<Stu> Students;
        Students.emplace_back(3, 3, 5); // pass
        Students.emplace_back(2, 2, 9); // pass
        Students.emplace_back(1, 3, 5); // pass
        Students.emplace_back(4, 1, 2); // not pass
        Students.emplace_back(5, 4, 7); // not pass
        Students.emplace_back(6, 1, 9); // pass
        Students.emplace_back(7, 6, 9); // not pass
        Students.emplace_back(8, 1, 1); // not pass
        auto pairIter = std::equal_range(Students.begin(), Students.end(), 3, EqualRangeStu());
        if (pairIter.first != Students.end() && pairIter.first != pairIter.second) {
            std::cout << pairIter.second - pairIter.first << " member(s) satified" << std::endl;
            decltype(pairIter.first) iter;
            for (iter = pairIter.first; iter != pairIter.second; iter++) {
                std::cout << "[index, min, max] = " << iter->index << " " << iter->min << " " 
                          << iter->max << std::endl;
            }
        } else {
            std::cout << "no member satified" << std::endl; 
        }
    }
    
    {
        /** 元素成员有序，结果准确 */
        std::vector<Stu> Students;
        Students.emplace_back(3, 3, 5); // pass
        Students.emplace_back(2, 2, 9); // pass
        Students.emplace_back(1, 3, 5); // pass
        Students.emplace_back(4, 1, 2); // not pass
        Students.emplace_back(5, 4, 7); // not pass
        Students.emplace_back(6, 1, 9); // pass
        Students.emplace_back(7, 6, 9); // not pass
        Students.emplace_back(8, 1, 1); // not pass
        // Students.emplace_back(9, 3, 2); // 非法数据，不应该存在
        std::sort(Students.begin(), Students.end(), SortStu());
        std::cout << "排序后:" << std::endl;
        for_each(Students.begin(), Students.end(), [](const Stu& s) {
            std::cout << "[index, min, max] = " << s.index << " " << s.min << " " << s.max << std::endl;
        });
        
        auto pairIter = std::equal_range(Students.begin(), Students.end(), 3, EqualRangeStu());
        if (pairIter.first != Students.end() && pairIter.first != pairIter.second) {
            std::cout << pairIter.second - pairIter.first << " member(s) satified" << std::endl;
            decltype(pairIter.first) iter;
            for (iter = pairIter.first; iter != pairIter.second; iter++) {
                std::cout << "[index, min, max] = " << iter->index << " " << iter->min << " " 
                          << iter->max << std::endl;
            }
        } else {
            std::cout << "no member satified" << std::endl; 
        }
    }
    
    return 0;
}