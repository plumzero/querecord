
#include <iostream>

void Throw() { throw 1; }
void NoBlockThrow() { Throw(); }
void BlockThrow() noexcept { Throw(); }

int main()
{
    try {
        Throw();
    } catch (...) {
        std::cout << "Found throw." << std::endl;   // print 'Found throw.'
    }

    try {
        NoBlockThrow();
    } catch (...) {
        std::cout << "Throw is not blocked." << std::endl;  // print 'Throw is not blocked.'
    }

    try {
        BlockThrow();   // terminate called after throwing an instance of 'int'
    } catch (...) {
        std::cout << "Try found throw." << std::endl;
    }

    return 0;
}
