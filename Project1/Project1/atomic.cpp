#include<iostream>
#include<atomic>
using namespace std;

int main() {
	atomic<int> a;
	a.load(std::memory_order_acquire);
	a.store(std::memory_order_release);
}