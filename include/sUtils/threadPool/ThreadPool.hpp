/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_THREADPOOL_THREADPOOL_HPP_
#define SUTILS_THREADPOOL_THREADPOOL_HPP_

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <utility>
#include <memory>
#include <future>
#include <condition_variable>

namespace sUtils {

class ThreadPool {
 public:
  ThreadPool() : ThreadPool(0) {}
  explicit ThreadPool(size_t threadNum) : m_threadNum(threadNum),
                                          m_threads(std::vector<std::thread>(threadNum)),
                                          m_stop(false) {
    for (size_t i = 0 ; i < m_threadNum ; ++i) {
      m_threads.emplace_back([&](){
        runTask();
      });
    }
  }

  virtual ~ThreadPool() {
    m_stop = true;
    m_cv.notify_all();

    for (auto& thread : m_threads) {
      if (thread.joinable()) {
        thread.join();
      }
    }
  }

  template<class F, class ...Args>
  std::future<typename std::result_of<F(Args...)>::type> pushTask(F&& func, Args&&... args) {
    if (m_stop) {
      throw std::runtime_error("Terminate ThreadPool");
    }

    using returnType = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<returnType()>>(
                  std::bind(std::forward<F>(func), std::forward<Args>(args)...));
    std::future<returnType> taskReturn = task->get_future();

    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_taskQueue.push([task](){ (*task)(); });
    }

    m_cv.notify_one();

    return taskReturn;
  }

  template<class C, class F, class ...Args>
  std::future<typename std::result_of<F(Args...)>::type> pushTask(C* obj, F&& func, Args&&... args) {
    if (m_stop) {
      throw std::runtime_error("Terminate ThreadPool");
    }

    using returnType = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<returnType()>>(
                  std::bind(obj, std::forward<F>(func), std::forward<Args>(args)...));
    std::future<returnType> taskReturn = task->get_future();

    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_taskQueue.push([task](){ (*task)(); });
    }

    m_cv.notify_one();

    return taskReturn;
  }

 private:
  void runTask() {
    while (true) {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cv.wait(lock, [&](){
        return !m_taskQueue.empty() || m_stop;
      });

      if (m_stop && m_taskQueue.empty()) {
        return;
      }

      std::function<void()> task = std::move(m_taskQueue.front());
      m_taskQueue.pop();

      lock.unlock();

      task();
    }
  }

 private:
  size_t m_threadNum;
  std::vector<std::thread> m_threads;
  std::queue<std::function<void()>> m_taskQueue;
  std::condition_variable m_cv;
  std::mutex m_mutex;

  bool m_stop;
};

}  // namespace sUtils

#endif  // SUTILS_THREADPOOL_THREADPOOL_HPP_
