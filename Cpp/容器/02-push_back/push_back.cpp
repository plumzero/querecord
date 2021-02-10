
#include <stdio.h>
#include <vector>
#include <list>

int main ()
{
    {
        printf("vector 测试\n");
        std::vector<int> vec;
        std::vector<int>::iterator it;
        
        vec.reserve(2);
        
        vec.push_back(10);        
        for (it = vec.begin(); it != vec.end(); it++) {
            printf("%p ", it);
        }
        printf("\n");
        
        vec.push_back(10);
        for (it = vec.begin(); it != vec.end(); it++) {
            printf("%p ", it);
        }
        printf("\n");
        
        vec.push_back(10);        
        for (it = vec.begin(); it != vec.end(); it++) {
            printf("%p ", it);
        }
        printf("\n");
    }
    
    {
        printf("list 测试\n");
        std::list<int> lst;
        std::list<int>::iterator it;
                
        lst.push_back(10);        
        for (it = lst.begin(); it != lst.end(); it++) {
            printf("%p ", it);
        }
        printf("\n");
        
        lst.push_back(10);
        for (it = lst.begin(); it != lst.end(); it++) {
            printf("%p ", it);
        }
        printf("\n");
        
        lst.push_back(10);        
        for (it = lst.begin(); it != lst.end(); it++) {
            printf("%p ", it);
        }
        printf("\n");
    }


    return 0;
}