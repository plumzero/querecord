
#include "ring.h"

int main()
{
    RingQueue<int> queue{4};
    std::cout << "capacity: " << queue.Capacity() << std::endl;
    queue.Print();
    
    queue.Put(1);
    queue.Print();

    queue.Put(2);
    queue.Print();

    queue.Put(3);
    queue.Print();

    int x;
    queue.Take(x);
    std::cout << x << "|";
    queue.Print();

    queue.Take(x);
    std::cout << x << "|";
    queue.Print();

    queue.Take(x);
    std::cout << x << "|";
    queue.Print();

    std::cout << std::endl;
    queue.Put(11);
    queue.Put(12);
    queue.Put(13);
    queue.Print();
    std::vector<int> lst;
    queue.Take(lst);
    std::cout << "lst.size=" << lst.size() << std::endl;
    queue.Print();

    return 0;
}