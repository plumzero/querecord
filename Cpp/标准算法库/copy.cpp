
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

struct CompCertRangeByType {
    bool operator()(const Cert& c, int type) { return c.type < type; }
    bool operator()(int type, const Cert& c) { return type < c.type; }
};

struct CompCertRangeByBundle {
    bool operator()(const Cert& c, int b) { return c.bundle < b; }
    bool operator()(int b, const Cert& c) { return b < c.bundle; }
};

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

    std::cout << "原始缓存:" << std::endl;
    std::sort(certs.begin(), certs.end(), CompCertSortByTBI());
    for (const auto& ele : certs) {
        std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
    }
    std::cout << std::endl;
    
    auto pairIterType = std::equal_range(certs.begin(), certs.end(), 2, CompCertRangeByType());
    if (pairIterType.first != certs.end() && pairIterType.first != pairIterType.second) {
        /** ok */
    } else {
        std::cout << "could not find type=" << 2 << std::endl;
        return -1;
    }
    
    auto pairIterBundle = std::equal_range(pairIterType.first, pairIterType.second, 1, CompCertRangeByBundle());
    if (pairIterBundle.first != pairIterType.second && pairIterBundle.first != pairIterBundle.second) {
        /** ok */
    } else {
        std::cout << "could not find bundle=" << 1 << std::endl;
        return -1;
    }

    std::cout << "原始缓存一部分，假设为 A:" << std::endl;
    for (auto iter = pairIterBundle.first; iter != pairIterBundle.second; iter++) {
        std::cout << iter->type  << " "<< iter->bundle << " " << iter->index << std::endl;
    }
    std::cout << std::endl;

    /** 保存为备份 */
    std::cout << "将 A 备份，假设备份后为 B:" << std::endl;
    std::vector<Cert> bakCerts(pairIterBundle.first, pairIterBundle.second);
    
    /** 改变原缓存中数据 */
    std::cout << "修改 A 缓存中数据:" << std::endl;
    for (auto iter = pairIterBundle.first; iter != pairIterBundle.second; iter++) {
        iter->index += 3;
    }
    for (auto iter = pairIterBundle.first; iter != pairIterBundle.second; iter++) {
        std::cout << iter->type  << " "<< iter->bundle << " " << iter->index << std::endl;
    }
    std::cout << std::endl;
    
    std::sort(certs.begin(), certs.end(), CompCertSortByTBI());
    for (const auto& ele : certs) {
        std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
    }
    std::cout << std::endl;
    
    /** 还原 */
    std::cout << "通过 B 还原 A:" << std::endl;
    std::copy(bakCerts.begin(), bakCerts.end(), pairIterBundle.first);
    for (auto iter = pairIterBundle.first; iter != pairIterBundle.second; iter++) {
        std::cout << iter->type  << " "<< iter->bundle << " " << iter->index << std::endl;
    }
    std::cout << std::endl;
    
    /** 整个缓存 */
    std::cout << "最终整个缓存:" << std::endl;
    std::sort(certs.begin(), certs.end(), CompCertSortByTBI());
    for (const auto& ele : certs) {
        std::cout << ele.type  << " "<< ele.bundle << " " << ele.index << std::endl;
    }
    std::cout << std::endl;

    return 0;
}