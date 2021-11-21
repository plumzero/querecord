
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include <thread>
#include <chrono>
#include <utility>
#include <functional>

#define _ECHO(format, ...)                \
    do {                                  \
        printf(format, ##__VA_ARGS__);    \
    } while (0)

#define ECHO(format, ...)                                            \
    do {                                                             \
        _ECHO("%lu %s " format "\n",                                  \
              (unsigned long)pthread_self(), now().c_str(), ##__VA_ARGS__);    \
    } while (0)

std::string now()
{
    struct timeval tus;
    char tmbuf[64] = { 0 };
    struct tm * st;
    
    gettimeofday(&tus, nullptr);
    st = localtime(&tus.tv_sec);
    strftime(tmbuf, sizeof(tmbuf), "%Y-%m-%d %H:%M:%S", st);
    
    return std::string(tmbuf, strlen(tmbuf));
}

class X
{
public:
    X(int c)
        : counter(c)
    {
        ECHO("construct function");
        th = std::thread(std::bind(&X::callback1, this, std::ref(is_running)));
    }
    
    X(X&& x)
        : counter(std::move(x.counter))
    {
        ECHO("move construct function: is_running=%d", is_running);
        th = std::thread(std::bind(&X::callback2, this, std::ref(is_running)));  // 创建新的线程栈使用
    }
    
    ~X()
    {
        ECHO("destruct function");
    }
    
    void callback1(const bool& running)
    {
        ECHO("callback1: only via once! running=%d", running);
        while (running) {
            ECHO("callback1: ==========> counter=%d", counter++);
            std::this_thread::sleep_for(std::chrono::seconds(1));   
        }
    }

    void callback2(const bool& running)
    {
        ECHO("callback2: only via once! running=%d", running);
        while (running) {
            ECHO("callback2: ----------> counter=%d", counter++);
            std::this_thread::sleep_for(std::chrono::seconds(1));   
        }
    }
    
    void clear_thread()
    {
        ECHO("clear thread");
        X::is_running = false;  // 让子线程停止，以便回收
        th.join();
        th.~thread();
    }
    
    std::thread th;
    static bool is_running;
    int counter;
};

bool X::is_running = true;

static void signal_handler(int signum)
{
    switch (signum)
    {
        case SIGALRM:
            ECHO("Get the alarm signal! changes of running status(1->0)");
            X::is_running = false;
            break;
        default:
            break;
    }
}

int main()
{
    signal(SIGALRM, signal_handler);
    
    X x(0);
    
    ECHO("main thread sleep for 3 seconds...");
    sleep(3);
    
    ECHO("main thread would send a alarm signal after 2 seconds...");
    alarm(2);
    
    ECHO("main thread sleep for 3 seconds...");
    sleep(3);
    
    x.clear_thread();   // 清除原来的线程栈
    
    X::is_running = true;
    X x1(std::move(x));
    
    ECHO("main thread sleep for 5 seconds...");
    sleep(5);
    
    x1.clear_thread();  // 清除线程栈
    ECHO("===== test over =====");
    
    return 0;
}