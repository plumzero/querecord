
#include <iostream>
#include <utility>

int main()
{
    int w1, w2;
    
    // int&& rrw1 = w1;             // error
    int&& rrw2 = std::move(w2);

    return 0;
}