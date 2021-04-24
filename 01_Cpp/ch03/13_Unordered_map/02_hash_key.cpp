
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <map>

#define SIZE_FOR_TEST      211

int main ()
{   
    {   
        std::unordered_map<int, int> intmap;
        
        printf("int=12345's hash key is %ld\n", intmap.hash_function()(12345));
        printf("\n");
    }
    
    return 0;
}