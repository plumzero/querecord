
#include "rq.hpp"

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <deque>
#include <list>
#include <queue>
#include <map>
#include <sys/time.h>

typedef struct __attribute__ ((__packed__)) {
    uint8_t     ver[3];
    uint8_t     orthocode;
    uint16_t    bodysize;
    uint16_t    msgid;
    uint64_t    origin;
    uint64_t    orient;
} NegoHeader;

int main()
{
    std::map<uint64_t, RingQueue<std::string, std::list<std::string>>> RQ;
    uint64_t id = 123456;
    
    RQ.insert(std::make_pair(id, RingQueue<std::string, std::list<std::string>>()));
        
    NegoHeader header;
    header.ver[0] = (uint8_t)'h';
    header.ver[1] = (uint8_t)'b';
    header.bodysize = 0;
    header.origin = 123;
    header.orient = 456;

    std::string tostream(std::string((const char *)&header, sizeof(NegoHeader)));
    // std::string tostream("Hello World");
    
    printf("tostream=%lu\n", tostream.size());
    
    RQ[id].push(tostream);
    
    printf("===== test over. =====\n");
    
    return 0;
}

