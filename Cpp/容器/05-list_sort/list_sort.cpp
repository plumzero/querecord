
#include <stdio.h>
#include <list>
#include <algorithm>

int main ()
{
    int array[] = {14, 22, 31, 3, 25, 54, 22, 43, 51, 68, 70};
    
    {
        std::list<int> lst(array, array + sizeof(array) / sizeof(array[0]));
        
        lst.sort();
        
        printf("lst.size=%lu\n", lst.size());
        
        std::list<int>::iterator it;
        for (it = lst.begin(); it != lst.end(); it++) {
            printf("%d ", *it);
        }
        printf("\n");
    }


    return 0;
}