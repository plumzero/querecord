
#include <stdio.h>
#include <string>
#include <iostream>

// 一天 86400 秒

const std::string next_n_seconds(const std::string& hhmmss, int secs)
{
    int val = std::atoi(hhmmss.c_str());
    int sec = val % 100;
    val /= 100;
    int min = val % 100;
    int hour = val / 100;

    int next = (hour * 3600 + min * 60 + sec + secs) % 86400;
    int next_h = next / 3600;
    next %= 3600;
    int next_m = next / 60;
    int next_s = next % 60;

    char buf[8] = { 0 };
    int ret = snprintf(buf, sizeof(buf), "%02d%02d%02d", next_h, next_m, next_s);

    return std::string(buf, ret);
}

int main()
{
    std::string hhmmss = "123456";
    int secs = 5 * 60;
    std::cout << hhmmss << "," << secs << ": " << next_n_seconds(hhmmss, secs) << std::endl;

    hhmmss = "120005";
    secs = 86399;
    std::cout << hhmmss << "," << secs << ": " << next_n_seconds(hhmmss, secs) << std::endl;

    hhmmss = "235601";
    secs = 5 * 60;
    std::cout << hhmmss << "," << secs << ": " << next_n_seconds(hhmmss, secs) << std::endl;
    
    return 0;
}