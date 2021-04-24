
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    int a[] = { 1, 1, 2, 3, 5, 8, 13, 21 };
    
    std::for_each(a, a + 8, [](int ele){
        std::cout << ele << std::endl;
    });
    
    return 0;
}

