
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>

#include <cmath>

using Params = std::poisson_distribution<>::param_type;

template<typename Iter>
void dist_plot(Iter beg_iter, Iter end_iter, size_t width = 90)
{
    std::map<int, size_t> plot_data;    // pair<value, frequency>
    
    auto pr = std::minmax_element(beg_iter, end_iter,
                                  [](const double v1, const double v2){ return v1 < v2; });
                                  
    for (int n{static_cast<int>(*pr.first)}; n < static_cast<int>(*pr.second); ++n) {
        plot_data.emplace(n, 0);
    }
    
    // count to map
    std::for_each(beg_iter, end_iter, [&plot_data](double value){
        ++plot_data[static_cast<int>(std::round(value))];
    });
    
    // Find maximum frequency to be plotted - must fit within page width
    size_t max_f { std::max_element(std::begin(plot_data), std::end(plot_data), [](const std::pair<int, size_t>& v1, const std::pair<int, size_t>& v2){ return v1.second < v2.second; })->second };
    
    // Draw distribution as histogram
    std::for_each(std::begin(plot_data), std::end(plot_data), [max_f, width](const std::pair<int, size_t>& v){
        std::cout << std::setw(3) << v.first << "-| "
                                  << std::string((width * v.second) / max_f, '*')
                                  << std::endl;
    });
}

int main()
{
    std::random_device rd;
    std::default_random_engine rng { rd() };
    std::poisson_distribution<> poisson;
    double mu{};
    const size_t sample_count { 20000 };
    std::vector<double> values(sample_count);
    
    while (true) {
        std::cout << "\nEnter values for the mean, or Ctrl+Z to end(for example: 5.5):";
        if ((std::cin >> mu).eof()) break;

        poisson.param(Params{ mu });
        std::generate(std::begin(values), std::end(values), [&poisson, &rng]{ return poisson(rng); });

        // Create data to plot histogram and plot it
        dist_plot(std::begin(values), std::end(values));
    }
    
    return 0;
}