

#include <iostream>

class Card
{
public:
    int SNo;
    std::string Code;
    std::string Type;

    Card(int sno, std::string code, std::string type)
    {
        SNo = sno;
        Code = code;
        Type = type;
    }
};

class MagicCard : public Card
{
public:
    using Card::Card;       // 声明使用基类构造函数
};

class MonsterCard : public Card
{
public:
    using Card::Card;       // 声明使用基类构造函数
};

int main()
{
    MagicCard magic(44656491, "DL1-086", "Continuous spell");
    MonsterCard monster(52038441, "ETCO-JP036", "Effect monster");
    
    std::cout << "magic" << std::endl;
    std::cout << "  SNo: " << magic.SNo << std::endl;
    std::cout << "  Code: " << magic.Code << std::endl;
    std::cout << "  Type: " << magic.Type << std::endl;
    
    std::cout << "monster" << std::endl;
    std::cout << "  SNo: " << monster.SNo << std::endl;
    std::cout << "  Code: " << monster.Code << std::endl;
    std::cout << "  Type: " << monster.Type << std::endl;
    
    return 0;
}