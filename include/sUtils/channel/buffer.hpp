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

uint64_t NowTimestamp() {
  auto now = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

class Buffer {
 public:
  Buffer() {}
  ~Buffer() {}

 public:

#pragma pack(4)
  struct Header {
    uint64_t timestamp;
    uint32_t len;
    uint32_t observed;
  };
#pragma unpack()
  
 public:
  Header header_;
  std::vector<uint8_t> buf_;
};

#endif // SUTILS_CHNNEL_BUFFER_HPP_
