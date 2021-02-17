
#include <iostream>
#include <deque>

int main()
{
    {
        std::deque<double> values(20);
        
        values[1] = 5.0;
        values[2] = 3.14;
    }
    
    {
        std::deque<double> values(20);
        
        values.at(1) = 5.0;
        values.at(2) = 3.14;
    }
    
    {
        std::deque<double> values(20);
        
        values.front() = 2.71828;
        values.back()  = 0.618;
    }
    
    return 0;
}