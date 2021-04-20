/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SIGSLOT_SIGSLOT_HPP_
#define SUTILS_SIGSLOT_SIGSLOT_HPP_

#include <iostream>
#include <vector>
#include <functional>
#include <utility>

class Signal {
 public:
  template<class F, class ...Args>
  void connect(F&& function, Args&&... args) {
    auto task = std::bind(std::forward<F>(function), std::forward<Args>(args)...);
    m_task = std::move([task](){ task(); });

    m_slots.emplace_back(task);
  }

  void emit() {
    for (auto slot : m_slots) {
      slot();
    }
  }

 private:
  std::vector<std::function<void()>> m_slots;
};

#endif  // SUTILS_SIGSLOT_SIGSLOT_HPP_
