
#include <iostream>
#include <vector>
#include <algorithm>

class Cert
{
public:
    Cert() {}
    Cert(int t, int b, int i)
        : type(t), bundle(b), index(i) {}
    ~Cert() {}
    
public:
    int             type;
    int             bundle;
    int             index;
};

struct CompCertSortByTBI
{
    bool operator()(const Cert& c1, const Cert& c2) {
        return c1.type < c2.type || (c1.type == c2.type && c1.bundle < c2. bundle)
            || (c1.type == c2.type && c1.bundle == c2.bundle && c1.index < c2.index);
    }
};

struct EqualRangeType
{
    bool operator()(const Cert &c, const int type) {
        return c.type < type;
    }
    bool operator()(const int type, const Cert &c) {
        return type < c.type;
    }
};

/** 只想说明，调用 std::equal_range 后，并不会影响集合原来的排序。 */
int main()
{
    std::vector<Cert> certs;
    
    certs.emplace_back(2, 2, 4);
    certs.emplace_back(2, 2, 5);
    certs.emplace_back(3, 1, 1);
    certs.emplace_back(1, 1, 1);
    certs.emplace_back(2, 1, 1);
    certs.emplace_back(2, 1, 2);
    certs.emplace_back(2, 1, 3);
    certs.emplace_back(3, 1, 3);
    certs.emplace_back(3, 2, 4);
    certs.emplace_back(2, 2, 1);
    certs.emplace_back(2, 2, 2);
    certs.emplace_back(2, 2, 3);
    certs.emplace_back(3, 1, 2);
    certs.emplace_back(3, 2, 1);
    certs.emplace_back(3, 2, 2);
    certs.emplace_back(3, 1, 4);
    certs.emplace_back(3, 2, 3);

    /** [1] 按照 Type 排序 */
    std::cout << "按照 Type 排序:" << std::endl;
    std::sort(certs.begin(), certs.end(), CompCertSortByTBI());
    for (const auto& ele : certs) {
        std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
    }
    std::cout << std::endl;
    
    /** [2] 使用 std::equal_range 从集合中取出指定迭代器对 */
    std::cout << "使用 equal_range:" << std::endl;
    auto pairIter = std::equal_range(certs.begin(), certs.end(), 2, EqualRangeType());
    if (pairIter.first != certs.end() && pairIter.first != pairIter.second) {
        decltype(pairIter.first) iter;
        for (iter = pairIter.first; iter != pairIter.second; iter++) {
            std::cout << iter->type << " " << iter->bundle << " " << iter->index << std::endl;
        }
        std::cout << std::endl;
    }
    
    /** [3] 执行 std::equal_range 后再观察集合中的排序 */
    std::cout << "使用 equal_range 后的排序:" << std::endl;
    for (const auto& ele : certs) {
        std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}