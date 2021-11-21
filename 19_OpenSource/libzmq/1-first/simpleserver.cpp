
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <string>

#include <zmq.hpp>

/**
 * 功能演示: REQ-REP 模式 / 简易Server
 */

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    
    while (true) {
        zmq::message_t request;
        socket.recv(&request);
        
        std::string msg((const char *)request.data(), request.size());
        printf("Server received request: %s\n", msg.c_str());
        printf("Now Server would take 2 seconds to deal with message.\n");
        sleep(2);
        
        char rep[] = { "Server sent this message" };
        zmq::message_t reply(rep, strlen(rep));
        socket.send(reply);
    }
    
    return 0;
}
