
#include <cstddef>
#include <stdexcept>

/**
 * 自定义特性化迭代器类
 */

namespace iterator_range
{
    template <typename T>
    class iterator
    {
    public:
        using value_type    = T;
        using size_type     = size_t;
    private:
        size_type           cursor_;
        const value_type    step_;
        value_type          value_;
    public:
        iterator(size_type cur_start, value_type begin_val, value_type step_val)
            : cursor_(cur_start), value_(begin_val), step_(step_val)
        {
            value_ += (step_ * cursor_);
        }
        value_type operator*() const { return value_; }
        bool operator!=(const iterator& rhs) const
        {
            return (cursor_ != rhs.cursor_);
        }
        iterator& operator++(void)
        {
            value_ += step_;
            ++ cursor_;
            return *this;
        }
    };
    
    template <typename T>
    class impl
    {
    public:
        using value_type        = T;
        using reference         = const value_type&;
        using const_reference   = const value_type&;
        using iterator          = const iterator_range::iterator<value_type>;
        using const_iterator    = const iterator_range::iterator<value_type>;
        using size_type         = typename iterator::size_type;
        
    private:
        const value_type    begin_;
        const value_type    end_;
        const value_type    step_;
        const size_type     max_count_;
        
        size_type get_adjusted_count(void)
        {
            if (step_ > 0 && begin_ >= end_)
                throw std::logic_error("End value must be greater than begin value.");
            else if (step_ < 0 && begin_ <= end_)
                throw std::logic_error("End value must be less than begin value.");
            
            size_type x = static_cast<size_type>((end_ - begin_) / step_);
            
            if (begin_ + (step_ * x) != end_)
                ++x;
            
            return x;
        }
    
    public:
        impl(value_type begin_val, value_type end_val, value_type step_val)
            : begin_(begin_val), end_(end_val), step_(step_val), max_count_(get_adjusted_count())
        {
        }
        
        size_type size(void) const
        {
            return max_count_;
        }
        
        const_iterator begin(void) const
        {
            return { 0, begin_, step_ };
        }
        
        const_iterator end(void) const
        {
            return { max_count_, begin_, step_ };
        }
    };
    
    template <typename T>
    iterator_range::impl<T> range(T end)
    {
        return { {}, end, 1 };
    }
    template <typename T>
    iterator_range::impl<T> range(T begin, T end)
    {
        return { begin, end, 1 };
    }
    template <typename T, typename U>
    auto range(T begin, T end, U step) -> iterator_range::impl<decltype(begin + step)>
    {
        // may be narrowing
        using r_t = iterator_range::impl<decltype(begin + step)>;
        return r_t(begin, end, step);
    }
};

#include <iostream>

using namespace iterator_range;

void test_range()
{
    std::cout << "range(15):";
    for (int i : range(15))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    std::cout << "range(2, 6):";
    for (auto i : range(2, 6))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    const int x = 2, y = 6, z = 3;
    std::cout << "range(2, 6, 3):";
    for (auto i : range(x, y, z))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    std::cout << "range(-2, -6, -3):";
    for (auto i : range(-2, -6, -3))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    std::cout << "range(10.5, 15.5):";
    for (auto i : range(10.5, 15.5))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    std::cout << "range(35, 27, -1):";
    for (auto i : range(35, 27, -1))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    std::cout << "range(2, 8, 0.5):";
    for (auto i : range(2, 8, 0.5))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    std::cout << "range(8, 7, -0.1):";
    for (auto i : range(8, 7, -0.1))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    
    std::cout << "range('a', 'z'):";
    for (auto i : range('a', 'z'))
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
}

int main()
{
    test_range();
    
    return 0;
}