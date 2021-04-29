#include <iostream>
#include <thread>
#include <chrono>

#include <sUtils/channel/shared_mem_session.hpp>

int main() {
	ShmSession session;

	session.Open("Test");

	while (1) {
		session.Read();
		// std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	session.Close();
}