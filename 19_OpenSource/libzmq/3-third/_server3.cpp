
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string>

#include <zmq.hpp>

typedef struct __attribute__ ((__packed__)) {
    uint8_t     ver[4];
    uint16_t    bodysize;
    uint32_t    ip;
} Header;

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    
    while (true)
    {        
        zmq::message_t request;
        socket.recv(request, zmq::recv_flags::dontwait);
        std::string strRequest((const char *)request.data(), request.size());
        printf("request.size=%lu,strRequest(size=%lu)\n", request.size(), strRequest.size());
                
        printf("Server received request: %s\n", strRequest.c_str());
        printf("Now Server would take 2 seconds to deal with message.\n");
        sleep(2);
        
        char buf[] = { "Hello World" };
        zmq::message_t reply(buf, strlen(buf));
        socket.send(reply);
    }
    
    return 0;
}
