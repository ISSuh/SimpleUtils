/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_TIMER_TIMER_HPP_
#define SUTILS_TIMER_TIMER_HPP_

#include <iostream>
#include <functional>
#include <utility>
#include <future>
#include <chrono>
#include <thread>
#include <memory>

namespace sUtils {

class Timer {
 public:
  explicit Timer(uint32_t delay, bool repeated = false)
    : m_stop(false), m_isRunning(false),
      m_repeated(repeated), m_delay(delay),
      m_currentTick(0) {}

  ~Timer() {}

  template<class F, class ...Args>
  void start(F&& function, Args&&... args) {
    if (isRunning()) {
      std::cout << "Timer already running\n";
      return;
    }

    // using returnType = typename std::result_of<F(Args...)>::type;
    auto task = std::bind(std::forward<F>(function), std::forward<Args>(args)...);

    m_task = std::move([task](){ task(); });

    m_runLoop = std::thread(&Timer::loop, this);
    m_runLoop.detach();

    m_isRunning = true;
  }

  void stop() {
    m_stop = true;
    m_isRunning = false;
  }

  bool isRunning() const { return m_isRunning; }

 private:
  void loop() {
    do {
      uint32_t delay = m_delay;
      while (delay) {
        if (m_stop) {
          std::cout << "Timer stop\n";
          return;
        }

        --delay;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }

      m_task();
    } while (m_repeated);
  }

 private:
  bool m_stop;
  bool m_isRunning;
  bool m_repeated;
  uint32_t m_delay;
  uint32_t m_currentTick;

  std::thread m_runLoop;
  std::function<void()> m_task;
};

}  // namespace sUtils

#endif  // SUTILS_TIMER_TIMER_HPP_
