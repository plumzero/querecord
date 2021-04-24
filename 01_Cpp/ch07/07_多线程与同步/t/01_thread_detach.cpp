/**
 * g++ -std=c++11 -g std_detach.cpp -o std_detach -lpthread
 *
 * 分离线程表示线程对象从主调线程(一般是main)中脱离，允许其独立执行。
 * 分离的线程与主调线程异步执行，不再阻塞。资源在线程执行完毕之后各自释放。
 * 此方法被调用后，线程对象成为 non-joinable 的，并且可以被安全地销毁。
 *
 * 我想，应该是一个较不常用的方法。
 */

#include <iostream>
#include <thread>
#include <chrono>

void pause_thread(int n) {
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended" << std::endl;
}

int main() {
	std::cout << "Spawning and detaching 3 threads..." << std::endl;
	std::thread (pause_thread, 1).detach();
	std::thread (pause_thread, 2).detach();
	std::thread (pause_thread, 3).detach();
	
	std::cout << "Done spawning threads." << std::endl;
	
	std::cout << "(the main thread will now pauses for 5 seconds)" << std::endl;
	
	pause_thread(5);
	
	return 0;
}