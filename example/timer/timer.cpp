/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>
#include <chrono>
#include <thread>

#include <sUtils/timer/Timer.hpp>

const uint32_t DELAY = 500;

void timeout() {
  static int count = 0;
  std::cout << "TimerOut count : " << count << " / " << &count << '\n';
  ++count;
}

int main() {
  sUtils::Timer t1(DELAY, true);
  t1.start(&timeout);

  std::this_thread::sleep_for(std::chrono::seconds(3));
}
