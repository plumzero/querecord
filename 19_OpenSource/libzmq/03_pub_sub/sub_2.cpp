
#include <iostream>
#include <string>

#include "zmq.hpp"

// PUB-SUB 模式
// 在不同端口上监听订阅

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::sub);

    std::string cno_a("friendly");
    std::string cno_b("unfriendly");

    // 在 5555 端口上订阅所有消息
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.bind("tcp://*:5555");

    // 在 5556 端口上只订阅 friendly 消息


    while (true) {
        zmq::message_t channel;
        socket.recv(channel, zmq::recv_flags::none);

        zmq::message_t msg;
        socket.recv(msg, zmq::recv_flags::none);
        
        std::cout << std::string((const char*)channel.data(), channel.size()) << ": " << std::string((const char*)msg.data(), msg.size()) << std::endl;
    }
    
    return 0;
}
