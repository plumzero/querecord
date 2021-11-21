
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <string>

#include <zmq.hpp>

/**
 * 功能演示: REQ-REP 模式 / Client
 */

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    socket.connect("tcp://localhost:5555");
    
    printf("Client would send a request to Server.\n");
    
    char req[] = { "Client sent this message" };
    zmq::message_t request(req, strlen(req));
    socket.send(request);
    
    zmq::message_t reply;
    socket.recv(&reply);
    
    std::string msg((const char *)reply.data(), reply.size());
    printf("Client received reply: %s\n", msg.c_str());
    
    return 0;
}
