
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <atomic>
#include <vector>
#include <algorithm>

#define COUNTER_FOR_EXE  1000000

typedef struct _bit_struct {
    unsigned int a:3;
    unsigned int b:5;
    unsigned int c:7;
} BitStruct;

BitStruct bs = { .a = 2, .b = 18, .c = 99 };

std::atomic<int> counter{0};
std::mutex mtx;

void change_bit_struct()
{       
    while (counter.load(std::memory_order_relaxed) < COUNTER_FOR_EXE) {
        bs.a++;
        bs.b++;
        bs.c++;
        
        counter++;
    }
}

int main()
{
    printf("开始执行前: a=%d,b=%d,c=%d\n", bs.a, bs.b, bs.c);
    
    printf("执行 %d 次后，a,b,c的值依次应该是: %d, %d, %d\n",
                        COUNTER_FOR_EXE,
                        (COUNTER_FOR_EXE % 4 + bs.a) % 4,
                        (COUNTER_FOR_EXE % 32 + bs.b) % 32,
                        (COUNTER_FOR_EXE % 128 + bs.c) % 128);
    
    std::vector<std::thread> vec;
    int i;
    for (i = 0; i < 10; i++) {
        std::thread th = std::thread(change_bit_struct);
        vec.emplace_back(std::move(th));
    }
    
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    
    printf("执行后: a=%d,b=%d,c=%d, counter=%d\n", bs.a, bs.b, bs.c, counter.load(std::memory_order_relaxed));
    
    return 0;
}



