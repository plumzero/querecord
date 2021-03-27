
#include <iostream>
#include <valarray>
#include <algorithm>
#include <iterator>
#include <random>

int main()
{
    std::uniform_int_distribution<int> dist{0, 25};
    std::random_device rd;
    std::default_random_engine rng{ rd() };
    std::valarray<char> letters(52);
    
    for (auto & ch : letters) {
        ch = 'a' + dist(rng);       // Random letter 'a' to 'z'
    }
    
    std::copy(std::begin(letters), std::end(letters), std::ostream_iterator<char>{ std::cout, " " });
    std::cout << std::endl;
    
    std::valarray<bool> vowels = letters == 'a' || letters == 'e' || letters == 'i' ||
                  letters == 'o' || letters == 'u';
    
    std::valarray<char> chosen { letters[vowels] };
    
    size_t count { chosen.size() };
    std::cout << count << " vowels were generated:\n";
    std::copy(std::begin(chosen), std::end(chosen), std::ostream_iterator<char>{ std::cout, " " });
    std::cout << std::endl;
                  
    
    return 0;
}