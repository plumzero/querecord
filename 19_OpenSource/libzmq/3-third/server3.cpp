
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string>

#include <zmq.hpp>

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    
    while (true) {
        zmq::message_t msgid;
        socket.recv(msgid, zmq::recv_flags::none);
        std::string strId((const char *)msgid.data(), msgid.size());
        printf("msgid.size=%lu,strId(size=%lu)=%s\n", msgid.size(), strId.size(), strId.c_str());
        
        zmq::message_t msgheader;
        socket.recv(msgheader, zmq::recv_flags::none);
        std::string strHeader((const char *)msgheader.data(), msgheader.size());
        printf("msgheadr.size=%lu,strHeader(size=%lu)=%s,header_flag=%d\n", msgheader.size(), strHeader.size(), strHeader.c_str(), std::atoi((const char *)msgheader.data()));
        
        int head = *(int *)msgheader.data();
        printf("head=%d\n", head);
        
        zmq::message_t request;
        socket.recv(request, zmq::recv_flags::dontwait);
        std::string strRequest((const char *)request.data(), request.size());
        printf("request.size=%lu,strRequest(size=%lu)=%s\n", request.size(), strRequest.size(), strRequest.c_str());
                
        printf("Server received request: %s\n", strRequest.c_str());
        printf("Now Server would take 2 seconds to deal with message.\n");
        sleep(2);
        
        char buf[] = { "Hello World" };
        zmq::message_t reply(buf, strlen(buf));
        socket.send(reply);
    }
    
    return 0;
}
