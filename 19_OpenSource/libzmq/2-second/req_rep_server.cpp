
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <string>

#include <sys/time.h>

#include <zmq.hpp>

/**
 * 功能演示: REQ-REP 模式 / Server
 */

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    int counter = 0;
    struct timeval bt, et;
    long bl, el;
    
    zmq::context_t context(1);              // 分别设置为 1 或 4
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    
    gettimeofday(&bt, nullptr);
    bl = bt.tv_sec * 1000 + bt.tv_usec / 1000;
    
    while (true) {
        zmq::message_t request;
        socket.recv(&request);
        
        std::string msg((const char *)request.data(), request.size());
        
        char rep[] = { "Server sent this message" };
        zmq::message_t reply(rep, strlen(rep));
        socket.send(reply);
        
        if (++counter == 10000) {
            break;
        }
    }
    
    gettimeofday(&et, nullptr);
    el = et.tv_sec * 1000 + et.tv_usec / 1000;
    
    printf("cost time: %ld\n", el - bl);
    
    return 0;
}
