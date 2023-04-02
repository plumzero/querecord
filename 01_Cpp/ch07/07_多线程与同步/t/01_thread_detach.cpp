
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