
#include "drive_timer.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

std::string clocktime()
{
    char buf[64] = { 0 };
    time_t t = std::time(nullptr);
    struct tm *st = std::localtime(&t);
    size_t len = std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", st);
    return std::string(buf, len);
}

int main()
{
    auto timer = new DriveTimer();

    uint64_t interval = 5000;
    timer->StartTimer(interval, [](){
        std::cout << "print this at " << clocktime() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    });

    int ticker = 0;
    while (ticker++ != 12) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete timer;

    std::cout << "expire at " << clocktime()  << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "exit at " << clocktime()  << std::endl;

    return 0;
}