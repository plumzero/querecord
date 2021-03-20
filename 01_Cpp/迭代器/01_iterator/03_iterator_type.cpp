
#include <iostream>
#include <iterator>
#include <typeinfo>
#include <vector>
#include <list>

int main()
{
    std::vector<int>  vi;
    std::vector<char> vc;
    
    std::iterator_traits<std::vector<int>::iterator>::iterator_category vector_iterator_traits_category;
    
    typedef std::iterator_traits<std::list<char>::iterator>  list_iterator_traits;
    
    if (typeid(vector_iterator_traits_category) == typeid(std::random_access_iterator_tag)) {
        std::cout << "vector's iterator is random access iterator" << std::endl;
    }
    
    if (typeid(list_iterator_traits::iterator_category) == typeid(std::bidirectional_iterator_tag)) {
        std::cout << "list's iterator is bidirectional access iterator" << std::endl;
    }
    
    if (typeid(vi.begin()) == typeid(vc.begin())) {
        std::cout << "value_type of vector<int>'s iterator is the same with vector<char>" << std::endl;
    } else {
        std::cout << "value_type of vector<int>'s iterator is not the same with vector<char>" << std::endl;
    }
    
    return 0;
}