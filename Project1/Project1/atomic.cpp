#include<iostream>
#include<thread>
#include<atomic>
using namespace std;

class SpinLock {
private:
	atomic_flag m;
public:
	SpinLock() : m{ATOMIC_FLAG_INIT} {}

	void lock() {
		while (1) {
			if (m.test_and_set(memory_order_acquire) == 0) break;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	void unlock() {
		m.clear(memory_order_release);
	}
};


int main() {
	



}