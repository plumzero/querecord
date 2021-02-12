
#include <iostream>

class Card
{
public:
    int SNo;
    std::string Code;
    std::string Type;
    
    std::string Attribute;
    std::string MonsterType;
    
    int Attack;
    int Defense;
    
    Card(int sno, std::string code, std::string type)
    {
        SNo = sno;
        Code = code;
        Type = type;
    }
    Card(int sno, std::string code, std::string type, 
         std::string attr, std::string monstertype)
        : Card(sno, code, type)
    {
        Attribute = attr;
        MonsterType = monstertype;
    }
    // 调用了委托构造函数，就不能用类成员初始化了
    // Card(int sno, std::string code, std::string type,
         // std::string attr, std::string monstertype,
         // int attack, int defense)
        // : Card(sno, code, type, attr, monstertype), Attack(attack), Defense(defense)
        // {
        // }
    // 只能通过成员赋值来初始化
    Card(int sno, std::string code, std::string type,
         std::string attr, std::string monstertype,
         int attack, int defense)
        : Card(sno, code, type, attr, monstertype)
        {
            Attack = attack;
            Defense = defense;
        }
};

int main()
{
    Card magic(44656491, "DL1-086", "Continuous spell");
    Card monster(52038441, "ETCO-JP036", "Effect monster", "Wind", "Zombie");
    
    std::cout << "magic" << std::endl;
    std::cout << "  SNo: " << magic.SNo << std::endl;
    std::cout << "  Code: " << magic.Code << std::endl;
    std::cout << "  Type: " << magic.Type << std::endl;
    
    std::cout << "monster" << std::endl;
    std::cout << "  SNo: " << monster.SNo << std::endl;
    std::cout << "  Code: " << monster.Code << std::endl;
    std::cout << "  Type: " << monster.Type << std::endl;
    std::cout << "  Attribute: " << monster.Attribute << std::endl;
    std::cout << "  MonsterType: " << monster.MonsterType << std::endl;
    
    return 0;
}
