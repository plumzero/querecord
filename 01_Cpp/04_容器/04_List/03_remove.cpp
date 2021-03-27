
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

int main()
{
    {
        std::list<int> numbers { 2, 5, 2, 3, 6, 7, 8, 2, 9 };
        
        numbers.remove(2);
        
        std::cout << numbers.size() << std::endl;
        std::ostream_iterator<int> oit(std::cout, " ");
        std::copy(numbers.begin(), numbers.end(), oit);     // 5 3 6 7 8 9
        std::cout << std::endl;
    }
    
    {
        std::list<int> numbers { 2, 5, 2, 3, 6, 7, 8, 2, 9 };
        
        numbers.remove_if([](int n){ return n % 2 == 0; });
        
        std::cout << numbers.size() << std::endl;
        std::ostream_iterator<int> oit(std::cout, " ");
        std::copy(numbers.begin(), numbers.end(), oit);     // 5 3 7 8
        std::cout << std::endl;
    }
    
    {
        int array[] = {14, 22, 31, 3, 25, 54, 22, 43, 51, 68, 70};
        
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
        int array[] = {14, 22, 31, 3, 25, 54, 22, 43, 51, 68, 70};
        
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