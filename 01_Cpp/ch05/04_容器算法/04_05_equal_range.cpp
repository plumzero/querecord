
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

int main()
{    
    std::list<int> values { 17, 11, 40, 13, 22, 54, 48, 70, 22, 61, 82, 78, 22, 89, 99, 92, 43 };
    
    std::cout << "The elements in the original sequence are:\n";
    std::copy(std::begin(values), std::end(values), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    int wanted { 22 };
    
    std::partition(std::begin(values), std::end(values), [wanted](int value) { return value < wanted; });
    std::partition(std::begin(values), std::end(values), [wanted](int value) { return !(wanted < value); });
    
    std::cout << "The elements after partitioning are:\n";
    std::copy(std::begin(values), std::end(values), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    auto pairIter = std::equal_range(std::begin(values), std::end(values), wanted);
    
    std::cout << "The lower bound for " << wanted
              << " is " << *pairIter.first
              << std::endl;
    
    std::cout << "The upper bound for " << wanted
              << " is " << *pairIter.second
              << std::endl;
              
    std::cout << "The elements found by equal_range() are:";
    std::copy(pairIter.first, pairIter.second, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    return 0;
}