
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <string>

#include <zmq.hpp>

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    socket.connect("tcp://localhost:5555");
    
    printf("Client would send a request to Server.\n");
    
    
    int mid = 100;
    std::string strId = std::string("td188|") + std::to_string(mid++);
    
    printf("strId=%s\n", strId.c_str());
    
    zmq::message_t msgid(strId.c_str(), strId.size());
    socket.send(msgid, zmq::send_flags::sndmore);
    
    int header_flag = 66;
    zmq::message_t msgheader(&header_flag, sizeof(int));
    socket.send(msgheader, zmq::send_flags::sndmore);
    
    char buf[] = { "Could you say Hello?" };
    zmq::message_t request(buf, strlen(buf));
    socket.send(request, zmq::send_flags::dontwait);
    
    zmq::message_t reply;
    socket.recv(&reply);
    
    std::string msg((const char *)reply.data(), reply.size());
    printf("Client received reply: %s\n", msg.c_str());
    
    return 0;
}
