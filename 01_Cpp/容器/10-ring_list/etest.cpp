
#include "rq.hpp"

#include <stdio.h>
#include <stdint.h>
#include <list>
#include <string>
#include <deque>
#include <queue>
#include <sys/time.h>

uint64_t ms_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

static unsigned char ucs[32] = {
    0x00, 0x20, 0x20, 0x20, 0x2B, 0x20, 0xE6, 0x9C,
    0xAC, 0xE5, 0x9C, 0xB0, 0xE7, 0x94, 0x9F, 0xE6,
    0x88, 0x90, 0xE5, 0xAF, 0x86, 0xE9, 0x92, 0xA5,
    0xE5, 0xAF, 0xB9, 0x28, 0xE8, 0xA1, 0x8D, 0xE7
};

int main()
{
    {
        RingQueue<std::string, std::deque<std::string>, 1024> Q;
        uint64_t bt, et;
        size_t i, c;
        
        bt = ms_time();
        
        for (c = 0; c < 1024; c++) {
            for (i = 0; i < 1024; i++) {
                Q.push(std::string(ucs, ucs + 32));
            }
            
            i = 0;
            while (! Q.empty()) {
                // printf("%lu ", Q.front().size());
                // if (++i % 32 == 0) printf("\n");
                Q.pop();
            }
        }
        
        et = ms_time();
        
        printf("\n\nspend %lu microseconds\n", et - bt);
    }

    
    {
        std::queue<std::string> Q;
        uint64_t bt, et;
        size_t i, c;
        
        bt = ms_time();
        
        for (c = 0; c < 1024; c++) {
            for (i = 0; i < 1024; i++) {
                Q.push(std::string(ucs, ucs + 32));
            }
            
            i = 0;
            while (! Q.empty()) {
                // printf("%lu ", Q.front().size());
                // if (++i % 32 == 0) printf("\n");
                Q.pop();
            }
        }
        
        et = ms_time();
        
        printf("\n\nspend %lu microseconds\n", et - bt);
    }


    


    
    return 0;
}
