/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_CHNNEL_LOCK_HPP_
#define SUTILS_CHNNEL_LOCK_HPP_

#include <pthread.h>
#include <atomic>
#include <thread>

class SpinLock {
 public:
  SpinLock() : lock_(true){}
  ~SpinLock() {}

  void Lock() {
    do {
      std::chrono::nanoseconds(100);
    } while(lock_.load(std::memory_order_acquire));
  }

  bool TryLock() {
    bool expected = true;
    return lock_.compare_exchange_strong(expected, true);
  }

  void Unlock() { lock_.store(false, std::memory_order_release); }

 private:
  std::atomic<bool> lock_;
};

class Lock {
 public:
  Lock() {
    pthread_mutexattr_init(&lock_attr_);
    pthread_mutexattr_settype(&lock_attr_, PTHREAD_MUTEX_NORMAL);
    pthread_mutexattr_setpshared(&lock_attr_, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&lock_, &lock_attr_);
  }

  ~Lock() {
    pthread_mutexattr_destroy(&lock_attr_);
    pthread_mutex_destroy(&lock_);
  }

  void lock() { pthread_mutex_lock(&lock_); }
  bool try_lock() { return pthread_mutex_trylock(&lock_); }
  void unlock() { pthread_mutex_unlock(&lock_); }

  pthread_mutex_t* get() { return &lock_; }

 private:
  pthread_mutex_t lock_;
  pthread_mutexattr_t lock_attr_;
};

class LockGuard {
 public:
  explicit LockGuard(Lock& lock) : lock_(lock) { lock.lock(); }
  ~LockGuard() { lock_.unlock(); }

 private:
  Lock& lock_;
};

class RWLock {
 public:
  RWLock() {
    pthread_rwlockattr_init(&rwlock_attr_);
    pthread_rwlockattr_setpshared(&rwlock_attr_, PTHREAD_PROCESS_SHARED);
    pthread_rwlock_init(&rwlock_, &rwlock_attr_);
  }

  ~RWLock() {
    pthread_rwlockattr_destroy(&rwlock_attr_);
    pthread_rwlock_destroy(&rwlock_);
  }

  void lock() { pthread_rwlock_wrlock(&rwlock_); }
  bool try_lock() { return !pthread_rwlock_trywrlock(&rwlock_); }

  void sharedable_lock() { pthread_rwlock_rdlock(&rwlock_); }
  bool try_sharedable_lock() { return !pthread_rwlock_tryrdlock(&rwlock_); }

  void unlock() { pthread_rwlock_unlock(&rwlock_); }

 private:
  pthread_rwlock_t rwlock_;
  pthread_rwlockattr_t rwlock_attr_;
};

class ConditionalVariable {
 public:
  ConditionalVariable() {
    pthread_condattr_init(&cond_attr_);
    pthread_condattr_setpshared(&cond_attr_, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&cond_, &cond_attr_);
  }

  ~ConditionalVariable() {
    pthread_condattr_destroy(&cond_attr_);
    pthread_cond_destroy(&cond_);
  }

  void wait(Lock *lock) { pthread_cond_wait(&cond_, lock->get()); }
  void notify() { pthread_cond_signal(&cond_); }

 private:
  pthread_cond_t cond_;
  pthread_condattr_t cond_attr_;
};

#endif // SUTILS_CHNNEL_LOCK_HPP_
