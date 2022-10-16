
#include <string>
#include <functional>
#include <type_traits>
#include <iostream>

#include "clsfunc.h"

template<typename _Proto, typename _Ros>
struct RosBagCallable
{
    // using _Func = std::function<void(const _Proto&, _Ros&)>;
    using _Func = std::function<void(typename std::add_lvalue_reference<typename std::add_const<_Proto>::type>::type, typename std::add_lvalue_reference<_Ros>::type)>;

    void operator() (const std::string& topic, const std::string& msg, _Func func) {
        std::cout << "RosBagCallable: topic = " << topic << std::endl;

        _Proto proto;
        proto.ParseFromString(msg);

        _Ros ros;
        func(proto, ros);
    }
};

// 测试六
int main()
{
    {
        ProtoStruct ps(3, 14, (const unsigned char*)"Hello World");
        auto stream = ps.ToString();
        
        using Listener = std::function<void(const std::string&)>;
        Listener binder = std::bind(RosBagCallable<ProtoStruct, RosStruct>(), "mytopic", std::placeholders::_1, FromProtoToRos);

        binder(stream);
    }

    return 0;
}
