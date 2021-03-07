
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <map>

#define SIZE_FOR_TEST      211

int main ()
{
    {
        std::unordered_map<int, int> intmap;
        
        intmap.rehash(SIZE_FOR_TEST);
        
        printf("bucket_count=%ld\n", intmap.bucket_count());
        printf("\n");
    }
    
    return 0;
}