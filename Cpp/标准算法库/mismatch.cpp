
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    版本一
    template<class InputIt1, class InputIt2, class BinaryPredicate>
    std::pair<InputIt1, InputIt2>
        mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        while (first1 != last1 && p(*first1, *first2)) {
            ++first1, ++first2;
        }
        return std::make_pair(first1, first2);
    }
    版本二(在一些机器上(如 RHEL7.5)不支持该版本，即便加上 -std=c++11)
    template<class InputIt1, class InputIt2, class BinaryPredicate>
    std::pair<InputIt1, InputIt2>
        mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p)
    {
        while (first1 != last1 && first2 != last2 && p(*first1, *first2)) {
            ++first1, ++first2;
        }
        return std::make_pair(first1, first2);
    }
    
    说明:
        1. 用猜拳游戏作示例，更易理解。
        2. mismatch 可以对非比较成员值不相同对象进行比较，这个功能很强大。比如当前示例
           中，name 是不同的，但是我们不关注这个，只看 type 是否 mismatch 。
    
    关键词:
        1. 输入迭代器
        2. 二元谓词，返回值为布尔类型
        3. 函数返回值: 返回一个 pair ，两个成员分别指向两个容器中第一次不匹配的元素成员。
    
    注意:
        1. 注意二元谓词的语义，返回 true 就继续 while， 返回 false 才退出
 */

enum FingerType {
    Hammer,
    Shear,
    Cloth
};

class FingerGuessing
{
public:
    FingerGuessing(int s, std::string n, FingerType t) : seq(s), name(n), type(t) {}
    ~FingerGuessing(){}
    
    int         seq;
    std::string name;
    FingerType  type;
    
};

struct CompType {
    bool operator()(const FingerGuessing& f1, const FingerGuessing& f2) { return f1.type == f2.type; }
};

bool comp_type(const FingerGuessing& f1, const FingerGuessing& f2) {
    return f1.type == f2.type;
}

int main()
{
    std::vector<FingerGuessing> FG1s;
    FG1s.emplace_back(1, "Herbert", Cloth);
    FG1s.emplace_back(2, "Baron",   Hammer);
    FG1s.emplace_back(3, "Darren",  Shear);
    FG1s.emplace_back(4, "Philip",  Hammer);
    FG1s.emplace_back(5, "Maxwell", Cloth);
    FG1s.emplace_back(6, "Jason",   Hammer);
    FG1s.emplace_back(7, "Kevin",   Hammer);
    
    std::vector<FingerGuessing> FG2s;
    FG2s.emplace_back(1, "Gilbert", Cloth);
    FG2s.emplace_back(2, "Alan",    Hammer);
    FG2s.emplace_back(3, "Julian",  Shear);
    FG2s.emplace_back(4, "Rhys",    Hammer);
    FG2s.emplace_back(5, "Jaxon",   Cloth);
    FG2s.emplace_back(6, "Buzz",    Shear);
    FG2s.emplace_back(7, "Lucy",    Hammer);
    
    /** [1] function object */
    auto pairIter = std::mismatch(FG1s.begin(), FG1s.end(), FG2s.begin(), CompType());
    if (pairIter.first != FG1s.end()) {
        std::cout << pairIter.first->seq << ": "
                  << pairIter.first->name << " VS " << pairIter.second->name << std::endl;
    } else {
        std::cout << "..." << std::endl;
    }
    /** [2] function pointer */
    pairIter = std::mismatch(FG1s.begin(), FG1s.end(), FG2s.begin(), comp_type);
    if (pairIter.first != FG1s.end()) {
        std::cout << pairIter.first->seq << ": "
                  << pairIter.first->name << " VS " << pairIter.second->name << std::endl;
    } else {
        std::cout << "..." << std::endl;
    }   
    /** [3] lambda expression */
    pairIter = std::mismatch(FG1s.begin(), FG1s.end(), FG2s.begin(), [](const FingerGuessing& f1, const FingerGuessing& f2) {
        return f1.type == f2.type;
    });
    if (pairIter.first != FG1s.end()) {
        std::cout << pairIter.first->seq << ": "
                  << pairIter.first->name << " VS " << pairIter.second->name << std::endl;
    } else {
        std::cout << "..." << std::endl;
    }
    
    return 0;
}