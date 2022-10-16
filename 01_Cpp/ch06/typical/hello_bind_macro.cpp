
#include <string>
#include <functional>
#include <type_traits>
#include <iostream>

#include "clsfunc.h"

#define Macro(topic, func, proto_type, ros_type, env_ptr) \
    do { \
        std::function<void(const std::string&)> binder = \
            std::bind(RosBagCls::RosBagCallable<proto_type, ros_type>(), topic, std::placeholders::_1, func, env_ptr); \
        binder(stream); \
    } while (0)

class RosBagCls
{
public:
    RosBagCls() : _str("Madolche") {}
    ~RosBagCls() {}

    template<typename _Proto, typename _Ros>
    struct RosBagCallable
    {
        // using _Func = std::function<void(const _Proto&, _Ros&)>;
        using _Func = std::function<void(typename std::add_lvalue_reference<typename std::add_const<_Proto>::type>::type, typename std::add_lvalue_reference<_Ros>::type)>;

        void operator() (const std::string& topic, const std::string& msg, _Func func, RosBagCls* env_ptr) {
            std::cout << "RosBagCallable: topic = " << topic << std::endl;

            _Proto proto;
            proto.ParseFromString(msg);

            std::cout << "RosBagCls: " << _internal << "," << env_ptr->_str << std::endl;

            _Ros ros;
            func(proto, ros);
        }
    };

    void test()
    {
        ProtoStruct ps(3, 14, (const unsigned char*)"Hello World");
        auto stream = ps.ToString();
        using Listener = std::function<void(const std::string&)>;
        Listener binder = std::bind(RosBagCls::RosBagCallable<ProtoStruct, RosStruct>(), "/my/topic", std::placeholders::_1, FromProtoToRos, this);
        binder(stream);
    }

    void test_macro()
    {
        ProtoStruct ps(2, 18, (const unsigned char*)"Hi World");
        auto stream = ps.ToString();

        Macro("/other/topic", FromProtoToRos, ProtoStruct, RosStruct, this);
    }
private:
    static int _internal;   // 对于静态成员可以不使用指针直接访问
    std::string _str;
};

int RosBagCls::_internal = 99;

// 测试七: 在模板类 D 中访问 B 类对象中的成员
// 首先将模板类 D 定义在 B 类中，然后为 D 的函数对象传入一个 B 类对象指针
int main()
{
    {
        RosBagCls rbc;
        
        rbc.test();
        rbc.test_macro();
    }

    return 0;
}
