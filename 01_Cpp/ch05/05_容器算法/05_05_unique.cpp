
#include <iostream>
#include <vector>
#include <algorithm>

/**
    可能的实现:
    template<class ForwardIt, class BinaryPredicate>
    ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        if (first == last)
            return last;
     
        ForwardIt result = first;
        while (++first != last) {
            if (!p(*result, *first) && ++result != first) {
                *result = std::move(*first);
            }
        }
        return ++result;
    }
    
    说明:
        1. 对有序出现的元素，消除首元素之外的元素。
    关键词:
        1. 前向迭代器
        2. 二元谓词，返回值为布尔类型；
        3. 谓词函数实现: bool pred(const Type1 &a, const Type2 &b);
        4. 函数返回值: 指向范围新结尾的前向迭代器
    注意:
        1. 调用 std::unique 之前必须对容器内元素按照当前需求排序。
        2. std::unique 是源内操作，返回的迭代器作为新的尾迭代器，进行缩小。
 */

class Weapon
{
public:
    Weapon(int t, int s) : type(t), sno(s) {}
    ~Weapon(){}
    int type;
    int sno;
};

struct CompUniqueWeapon
{
    bool operator()(const Weapon& w1, const Weapon& w2) { return w1.type == w2.type; }
};


bool comp_unique_weapon(const Weapon& w1, const Weapon& w2)
{
    return w1.type == w2.type;
}

struct CompSortWeapon
{
    bool operator()(const Weapon& w1, const Weapon& w2) {
        return w1.type < w2.type;
    }
};

int main()
{
    {
        /** [1] function object */
        std::vector<Weapon> Weapons;
        
        Weapons.emplace_back(1, 189273);
        Weapons.emplace_back(3, 237829);
        Weapons.emplace_back(5, 277463);
        Weapons.emplace_back(3, 892834);
        Weapons.emplace_back(9, 278635);
        Weapons.emplace_back(9, 173829);
        Weapons.emplace_back(2, 208372);
        Weapons.emplace_back(1, 327638);
        Weapons.emplace_back(8, 873724);
        
        std::sort(Weapons.begin(), Weapons.end(), CompSortWeapon());

        auto newEndIter = std::unique(Weapons.begin(), Weapons.end(), CompUniqueWeapon());
        for (auto iter = Weapons.begin(); iter != newEndIter; iter++) {
            std::cout << iter->type << " " << iter->sno << std::endl;
        }
        std::cout << std::endl;
    }
    
    {
        /** [2] function pointer */
        std::vector<Weapon> Weapons;
        
        Weapons.emplace_back(1, 189273);
        Weapons.emplace_back(3, 237829);
        Weapons.emplace_back(5, 277463);
        Weapons.emplace_back(3, 892834);
        Weapons.emplace_back(9, 278635);
        Weapons.emplace_back(9, 173829);
        Weapons.emplace_back(2, 208372);
        Weapons.emplace_back(1, 327638);
        Weapons.emplace_back(8, 873724);
        
        std::sort(Weapons.begin(), Weapons.end(), CompSortWeapon());
        
        auto newEndIter = std::unique(Weapons.begin(), Weapons.end(), comp_unique_weapon);
        for (auto iter = Weapons.begin(); iter != newEndIter; iter++) {
            std::cout << iter->type << " " << iter->sno << std::endl;
        }
        std::cout << std::endl;
    }

    {
        /** [3] lambda expression */
        std::vector<Weapon> Weapons;
        
        Weapons.emplace_back(1, 189273);
        Weapons.emplace_back(3, 237829);
        Weapons.emplace_back(5, 277463);
        Weapons.emplace_back(3, 892834);
        Weapons.emplace_back(9, 278635);
        Weapons.emplace_back(9, 173829);
        Weapons.emplace_back(2, 208372);
        Weapons.emplace_back(1, 327638);
        Weapons.emplace_back(8, 873724);
        
        std::sort(Weapons.begin(), Weapons.end(), CompSortWeapon());
        
        auto newEndIter = std::unique(Weapons.begin(), Weapons.end(), [](const Weapon& w1, const Weapon& w2) {
            return w1.type == w2.type;
        });
        for (auto iter = Weapons.begin(); iter != newEndIter; iter++) {
            std::cout << iter->type << " " << iter->sno << std::endl;
        }
    }
        
    return 0;
}