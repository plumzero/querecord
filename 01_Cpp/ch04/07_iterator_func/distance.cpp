
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<std::string> vs{ "SYMBOL",
                                 "raw_wangbo_close",
                                 "raw_wangbo_high",
                                 "raw_wangbo_highlimited",
                                 "raw_wangbo_low",
                                 "raw_wangbo_lowlimited",
                                 "raw_wangbo_open",
                                 "raw_wangbo_preclose",
                                 "raw_wangbo_totalvolume",
                                 "raw_wangbo_turnover" };
    
    {
        std::string s = "SYMBOL";

        int index = std::distance(vs.begin(), std::find(vs.begin(), vs.end(), s));

        std::cout << s << "'s index is " << index << std::endl;
    }

    {
        std::string s = "raw_wangbo_turnover";

        int index = std::distance(vs.begin(), std::find(vs.begin(), vs.end(), s));

        std::cout << s << "'s index is " << index << std::endl;
    }

    {
        std::string s = "no_this_element";

        int index = std::distance(vs.begin(), std::find(vs.begin(), vs.end(), s));

        std::cout << s << "'s index is " << index << std::endl;
    }

    return 0;
}