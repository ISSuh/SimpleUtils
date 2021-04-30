/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_CHNNEL_BUFFER_HPP_
#define SUTILS_CHNNEL_BUFFER_HPP_

#include <stdint.h>

#include <vector>
#include <atomic>
#include <chrono>
#include <algorithm>

#include "lock.hpp"

uint64_t NowTimestamp() {
  auto now = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

class Counter {
 public:
  Counter() : count_(0) {}

  void Increase() { count_.fetch_add(1); }
  void Decrease() { count_.fetch_sub(1); }

  bool IsZero() {
    uint32_t expect = 0;
    return count_.compare_exchange_strong(expect, 0);
  }

  uint8_t GetCount() const { return count_.load(); }

 private:
  std::atomic<uint32_t> count_;
};

struct Blob {
  uint64_t timestamp;
  uint len;
  uint8_t data[1024 * 1024];
};

struct Bucket {
  RWLock lock;
  Counter semaphoe;
  Blob blob;
};

class Memory {
 public:
  Memory() = default;
  ~Memory() = default;

  enum {
    BUCKET_SIZE = 10
  };

  bool TryWrite(uint8_t* buf, size_t len, uint32_t* idx) {
    uint32_t index = *idx;
    Bucket& bucket = bucket_[index];

    if (!bucket.semaphoe.IsZero()) {
      return false;
    }

    {
      LockGuard bucket_lock_guard(bucket.lock);
      std::cout << "index -" << index << " / after lock\n";
      bucket.blob.timestamp = NowTimestamp();
      bucket.blob.len = len;
      std::copy(buf, buf + len, bucket.blob.data);

      *idx = index >= BUCKET_SIZE ? 0 : ++index;
    }

    return true;
  }

  bool TryRead(uint8_t* buf, size_t *len, uint32_t* idx) {
    uint32_t index = *idx;
    Bucket& bucket = bucket_[index];

    {
      bucket.semaphoe.Increase();
      if (!bucket.lock.try_sharedable_lock()) {
        bucket.semaphoe.Decrease();
        return false;
      } else {
        std::copy(bucket.blob.data, bucket.blob.data + bucket.blob.len, buf);
        *len = bucket.blob.len;
        *idx = index >= BUCKET_SIZE ? 0 : ++index;

        bucket.lock.unlock();
      }
    }

    bucket.semaphoe.Decrease();
    return true;
  }

  void IncreseObserve() { observe_.Increase(); }
  void DecreseObserve() { observe_.Decrease(); }
  uint32_t GetObserved() const { return observe_.GetCount(); }

 private:
  RWLock lock_;
  Counter observe_;
  Bucket bucket_[BUCKET_SIZE];
};

#endif  // SUTILS_CHNNEL_BUFFER_HPP_
