
#include <stdio.h>
#include <deque>

int main ()
{
    std::deque<int> deq;
    
    printf("max_size=%lu\n", deq.max_size());
    
    deq.resize(10, 100);
    
    printf("max_size=%lu\n", deq.max_size());
    printf("size=%lu\n", deq.size());
    
    size_t i;
    for (i = 0; i < deq.size(); i++) {
        printf("%p ", &deq[i]);
    }
    printf("\n");

    deq.push_front(200);
    deq.push_front(200);
    deq.push_front(200);
    deq.push_front(200);
    deq.push_front(200);
    
    for (i = 0; i < deq.size(); i++) {
        printf("%p ", &deq[i]);
    }
    printf("\n");

    return 0;
}