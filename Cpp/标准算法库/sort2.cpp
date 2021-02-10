
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

struct CompCertSortByType
{
    bool operator()(const Cert& c1, const Cert& c2) { return c1.type < c2.type; }
};

struct CompCertSortByTB
{
    bool operator()(const Cert& c1, const Cert& c2) {
        return c1.type < c2.type || (c1.type == c2.type && c1.bundle < c2.bundle);
    }
};

struct CompCertSortByTBI
{
    bool operator()(const Cert& c1, const Cert& c2) {
        return c1.type < c2.type || (c1.type == c2.type && c1.bundle < c2. bundle)
            || (c1.type == c2.type && c1.bundle == c2.bundle && c1.index < c2.index);
    }
};

int main()
{
    {
        /** [1] 按 type 排序 */
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
    
        std::cout << "按照 Type 排序:" << std::endl;
        std::sort(certs.begin(), certs.end(), CompCertSortByType());
        for (const auto& ele : certs) {
            std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
        }
        std::cout << std::endl;
    }
    
    {
        /** [2] 按 type bundle 排序 */
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
    
        std::cout << "按照 Type 和 Bundle 排序:" << std::endl;
        std::sort(certs.begin(), certs.end(), CompCertSortByTB());
        for (const auto& ele : certs) {
            std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
        }
        std::cout << std::endl;
    }
    
    {
        /** [3] 按 type bundle index 排序 */
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
    
        std::cout << "按照 Type, Bundle 和 Index 排序:" << std::endl;
        std::sort(certs.begin(), certs.end(), CompCertSortByTBI());
        for (const auto& ele : certs) {
            std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
        }
        std::cout << std::endl;
    }
    
    return 0;
}