
#include <stdio.h>
#include <list>

bool mycomparison(double first, double second)
{
    return first < second;
}

int main()
{
    std::list<double> first, second;
    
    first.push_back(3.1);
    first.push_back(2.2);
    first.push_back(2.9);
    
    second.push_back(3.7);
    second.push_back(7.1);
    second.push_back(1.4);
    second.push_back(2.1);

    first.sort();
    second.sort();
        
    first.merge(second, mycomparison);
    
    for (const auto & ele : first) {
        printf("%.1f ", ele);
    }
    printf("\n");
    
    return 0;
}
