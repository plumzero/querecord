
#include <iostream>
#include <fstream>
#include <sstream>

#include "config.h"

int main()
{   
    std::cout << CONF_PATH << std::endl;
    std::cout << VERSION_MAJOR << std::endl;
    std::cout << VERSION_MINOR << std::endl;

    return 0;
}
