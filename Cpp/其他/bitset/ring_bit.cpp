
#include <iostream>
#include <bitset>

template <size_t N>
class BitRing
{
public:
    BitRing(const BitRing &) = delete;
    BitRing &operator=(const BitRing &) = delete;
    BitRing(const BitRing &&) = delete;
    BitRing &operator=(const BitRing &&) = delete;
    BitRing() { mask.reset(); cur = 0; }
    
    void set()
    {
        mask[cur++ % N] = 1;
    }
    void unset()
    {
        mask[cur++ % N] = 0;
    }
    double ratio()
    {
        size_t i;
        int t = 0;
        for (i = 0; i < mask.size(); i++) {
            if (mask.test(i)) {
                ++t;
            }
        }
        
        return (double) t / N;
    }
    
public:
    std::bitset<N> mask;
	int cur;
};

int main()
{
    BitRing<4> bits;
    
    bits.set();
    std::cout << "bits=" << bits.mask.to_string() << ", ratio=" << bits.ratio() << std::endl;
	
    bits.set();
    std::cout << "bits=" << bits.mask.to_string() << ", ratio=" << bits.ratio() << std::endl;
	
    bits.unset();
    std::cout << "bits=" << bits.mask.to_string() << ", ratio=" << bits.ratio() << std::endl;
	
    bits.set();
    std::cout << "bits=" << bits.mask.to_string() << ", ratio=" << bits.ratio() << std::endl;
    
    bits.unset();
    std::cout << "bits=" << bits.mask.to_string() << ", ratio=" << bits.ratio() << std::endl;
	
    return 0;
}