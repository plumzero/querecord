

// constructing vectors
#include <iostream>
#include <vector>
#include <utility>

class A
{
public:
    int i_;
    std::vector<int> vec_;
public:
    A() {}
    A(A&& a) { std::cout << "move" << std::endl; i_ = std::move(a.i_); vec_ = std::move(a.vec_); }
    void print()
    {
        std::cout << "=== A content ===" << std::endl;
        std::cout << "i_=" << i_ << std::endl;
        std::cout << "vec_.size=" << vec_.size() << std::endl;
        for (auto & ele : vec_) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
};

int main ()
{
    A a;
    
    a.i_ = 1;
    a.vec_.push_back(1);
    a.vec_.push_back(2);
    a.vec_.push_back(3);
    
    a.print();
    
    A ra = std::move(a);
    ra.print();
    
    a.print();
    
    return 0;
}