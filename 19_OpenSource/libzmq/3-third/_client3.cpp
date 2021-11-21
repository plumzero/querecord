
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <string>

#include <zmq.hpp>

typedef struct __attribute__ ((__packed__)) {
    uint8_t         ver[2];
    uint32_t        id;
    uint16_t        flag;
    uint16_t        bodysize;
    uint32_t        ip;
    unsigned char   buf[0];
} Header;

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    socket.connect("tcp://localhost:5555");
    
    printf("Client would send a request to Server.\n");
    
    char buf[] = { "Could you say Hello?" };
    size_t buflen = strlen(buf);
    
    Header * header = (Header*)calloc(1, sizeof(Header) + buflen);
    
    header->ver[0] = (uint8_t)'t';
    header->ver[1] = (uint8_t)'d';
    header->id = htonl(188);
    header->flag = htons(66);
    header->bodysize = buflen;
    
    const char * sip = "192.168.1.5";
    int a, b, c, d;
    int ret = sscanf(sip, "%d.%d.%d.%d", &a, &b, &c, &d);
    if (ret != 4) {
        printf("sscanf error(%d)\n", ret);
        return -1;
    }
    header->ip = htonl(((uint32_t) a << 24) | ((uint32_t) b << 16) | c << 8 | d);
    memcpy(header->buf, buf, header->bodysize);
    
    zmq::message_t request(header, sizeof(Header) + buflen);
    socket.send(request, zmq::send_flags::dontwait);
    
    zmq::message_t reply;
    socket.recv(&reply);
    
    std::string msg((const char *)reply.data(), reply.size());
    printf("Client received reply: %s\n", msg.c_str());
    
    return 0;
}
