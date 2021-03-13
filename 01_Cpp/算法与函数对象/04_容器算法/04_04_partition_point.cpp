
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

int main()
{
    std::vector<double> temperatures { 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
    
    auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0) / temperatures.size();
    
    auto predicate = [average](double t){ return t < average; };
    
    std::stable_partition(std::begin(temperatures), std::end(temperatures), predicate);
    
    auto iter = std::partition_point(std::begin(temperatures), std::end(temperatures), predicate);
    
    std::cout << "Elements in the first partition: ";
    std::copy(std::begin(temperatures), iter, std::ostream_iterator<double>(std::cout, " "));

    std::cout << "\nElements in the second partition: ";
    std::copy(iter, std::end(temperatures), std::ostream_iterator<double>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}