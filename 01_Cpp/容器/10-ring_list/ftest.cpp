
#include "rq.hpp"

#include <stdio.h>
#include <list>
#include <string>

int main()
{
    RingQueue<std::string, std::list<std::string>, 8> rq;
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }

    rq.push("A");
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }

    rq.push("B");
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
    
    rq.push("C");
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
            
    rq.push("D");
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
    
    rq.push("E");
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
    
    rq.pop();
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
    
    rq.pop();
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
            
    rq.pop();
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
            
    rq.pop();
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
    
    rq.pop();
    printf("sz=%lu, rq(size=%lu,empty=%d,full=%d",
            rq.c.size(), rq.size(), rq.empty(), rq.full());
    if (! rq.empty()) {
        printf(",front=%s,back=%s)\n", rq.front().c_str(), rq.back().c_str());
    } else {
        printf(")\n");
    }
    
    
    return 0;
}
