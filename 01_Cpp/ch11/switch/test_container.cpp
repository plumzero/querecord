
#include "container.h"

int main()
{
    Container<int, std::vector> cvec;

    std::cout << std::boolalpha << "empty: " << cvec.empty() << std::endl;

    SwitchContainer<int, std::list> s;
    s.Print();
    s.Switch();
    s.Print();
    s.Switch();
    s.Print();
    s.PushBack(1);
    s.PushBack(2);
    s.PushBack(3);
    s.Print();

    return 0;
}
