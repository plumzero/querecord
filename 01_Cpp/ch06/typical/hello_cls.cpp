
#include <string>
#include <functional>
#include <type_traits>
#include <iostream>

#include "clsfunc.h"

class MyCls {
public:
    MyCls() {}
    ~MyCls() {}

    template<typename _Proto, typename _Ros,
            class _Func = std::function<void(typename std::add_lvalue_reference<typename std::add_const<_Proto>::type>::type, typename std::add_lvalue_reference<_Ros>::type)>>
    void RosBagCallback(const std::string &topic, const std::string& msg, _Func fn)
    {
        std::cout << "MyCls::RosBagCallback: " << topic << std::endl;

        _Proto proto;
        proto.ParseFromString(msg);

        _Ros ros;
        fn(proto, ros);
    }
};

// 测试三
int main()
{
    {
        ProtoStruct ps(3, 14, (const unsigned char*)"Hello World");
        auto stream = ps.ToString();

        auto fn = std::bind(FromProtoToRos, std::placeholders::_1, std::placeholders::_2);

        MyCls cls;
        cls.RosBagCallback<ProtoStruct, RosStruct>("yourtopic", stream, fn);
    }

    return 0;
}
