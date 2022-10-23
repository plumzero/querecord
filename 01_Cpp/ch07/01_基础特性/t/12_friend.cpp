
#include <iostream>
#include <string>

template <typename T>
class Defender
{
public:
    friend T;
private:
    int pos_x = 15;
    int pos_y = 0;
    int speed = 2;
    int stamina = 20;
};

template <typename T>
class Attacker
{
    friend T;
public:
    void print() { T::show(pos_x, pos_y); }
private:
    int pos_x = 0;
    int pos_y = -30;
    int speed = 3;
    int stamina = 100;
};

struct Print
{
    static void show(int x, int y) {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

int main()
{
    // 以 Defender 为例，它在成员变量都是私有的，外部无法直接访问，但是如果将模板参数传入一个 int, 那是不是就可以访问了
    Defender<int> defender;
    // std::cout << "defender.pos_x = " << defender.pos_x << std::endl;
    // std::cout << "defender.pos_y = " << defender.pos_y << std::endl;
    // 结果是不可行的

    Attacker<Print> attacker;
    attacker.print();

    return 0;
}