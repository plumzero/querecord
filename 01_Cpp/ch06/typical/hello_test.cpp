
#include <iostream>

#include "clsfunc.h"

// 测试一
int main()
{
    {
        ProtoStruct ps(3, 14, (const unsigned char*)"Hello World");
        ps.Print();
        auto stream = ps.ToString();
        std::cout << "stream.size = " << stream.size() << std::endl;

        ProtoStruct ps_copy;
        ps_copy.ParseFromString(stream);
        ps_copy.Print();
    }

    return 0;
}
