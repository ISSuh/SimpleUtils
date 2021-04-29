/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_CHNNEL_BUFFER_HPP_
#define SUTILS_CHNNEL_BUFFER_HPP_

#include <stdint.h>

#include <vector>
#include <chrono>
#include <atomic>

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
  Lock lock;
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
    
    {
      LockGuard bucket_lock_guard(bucket.lock);
      
      if (!bucket.semaphoe.IsZero()) {
        return false;
      }

      bucket.blob.timestamp = NowTimestamp();
      bucket.blob.len = len;
      std::copy(buf, buf + len, bucket.blob.data);
      
      {
        LockGuard memory_lock_guard(lock_);
        *idx = index >= BUCKET_SIZE ? 0 : ++index;
      }
    }      

    return true;
  }

  bool TryRead(uint8_t* buf, size_t *len, uint32_t* idx) {
    uint32_t index = *idx;
    Bucket& bucket = bucket_[index];

    {
      LockGuard memory_lock_guard(lock_);

      bucket.semaphoe.Increase();
      if (!bucket.lock.try_lock()) {
        bucket.semaphoe.Decrease();
        return false;
      } else {
        bucket.lock.unlock();
      }

      std::copy(bucket.blob.data, bucket.blob.data + bucket.blob.len, buf);
      *len = bucket.blob.len;
      *idx = index >= BUCKET_SIZE ? 0 : ++index;
    }

    bucket.semaphoe.Decrease();
    return true;
  }

  void IncreseObserve() { observe_.Increase(); }
  void DecreseObserve() { observe_.Decrease(); }
  uint32_t GetObserved() const { return observe_.GetCount(); }

 private:
  Lock lock_;
  Counter observe_;
  Bucket bucket_[BUCKET_SIZE];
};

class Buffer {
 public:
  const size_t kDefaultMemorySize = 64 * 1024 * 1024;

  Buffer() {}
  ~Buffer() {}

// #pragma pack(4)
  struct Header {
    uint64_t timestamp;
    uint32_t len;
    std::atomic<uint32_t> observed;
    RWLock lock;
    ConditionalVariable cv;
  };
// #pragma unpack()

  size_t HeaderLen() { return sizeof(header_); }

 public:
  Header header_;
  uint8_t buf_[64 * 1024 * 1024];
};

#endif // SUTILS_CHNNEL_BUFFER_HPP_
