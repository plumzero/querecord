
#include <stdio.h>
#include <list>

int main ()
{
    int array[] = {14, 22, 31, 3, 25, 54, 22, 43, 51, 68, 70};
    
    {
        std::list<int> lst(array, array + sizeof(array) / sizeof(array[0]));
        
        lst.remove(22);
        
        printf("lst.size=%lu\n", lst.size());
        
        std::list<int>::iterator it;
        for (it = lst.begin(); it != lst.end(); it++) {
            printf("%d ", *it);
        }
        printf("\n");
    }
    
    {
        std::list<int> lst(array, array + sizeof(array) / sizeof(array[0]));
        
        lst.remove_if([](const int& ele)-> bool { return ele < 30; });
        
        printf("lst.size=%lu\n", lst.size());
        
        std::list<int>::iterator it;
        for (it = lst.begin(); it != lst.end(); it++) {
            printf("%d ", *it);
        }
        printf("\n");
    }


    return 0;
}