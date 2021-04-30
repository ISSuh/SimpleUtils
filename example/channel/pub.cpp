#include <iostream>
#include <thread>
#include <chrono>

#include <sUtils/channel/shared_mem_session.hpp>
#include <sUtils/channel/lock.hpp>

int main() {
  ShmSession session;

  session.Open("Test");

  int i = 0;
  while (1) {
    std::string tmp = "TEST-" + std::to_string(i);
    session.Write(tmp);
    std::cout << tmp << std::endl;

    ++i;
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  session.Close();
}
