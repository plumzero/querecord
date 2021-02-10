
#include <iostream>
#include <vector>
#include <algorithm>

/**
    unique_copy 的源外拷贝版本
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
        std::vector<Weapon> Weapons, WeaponsCopy;
                
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

        std::unique_copy(Weapons.begin(), Weapons.end(), std::back_inserter(WeaponsCopy), CompUniqueWeapon());
        for (const auto & ele : WeaponsCopy) {
            std::cout << ele.type << " " << ele.sno << std::endl;
        }
        std::cout << std::endl;
    }
    
    {
        /** [2] function pointer */
        std::vector<Weapon> Weapons, WeaponsCopy;
        
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
        
        std::unique_copy(Weapons.begin(), Weapons.end(), std::back_inserter(WeaponsCopy), comp_unique_weapon);
        for (const auto & ele : WeaponsCopy) {
            std::cout << ele.type << " " << ele.sno << std::endl;
        }
        std::cout << std::endl;
    }

    {
        /** [3] lambda expression */
        std::vector<Weapon> Weapons, WeaponsCopy;
        
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
        
        std::unique_copy(Weapons.begin(), Weapons.end(), std::back_inserter(WeaponsCopy),
                         [](const Weapon& w1, const Weapon& w2){
            return w1.type == w2.type;
        });
        for (const auto & ele : WeaponsCopy) {
            std::cout << ele.type << " " << ele.sno << std::endl;
        }
    }
        
    return 0;
}