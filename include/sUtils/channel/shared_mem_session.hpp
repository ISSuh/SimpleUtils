/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_CHNNEL_SHARED_MEMORY_SESSION_HPP_
#define SUTILS_CHNNEL_SHARED_MEMORY_SESSION_HPP_

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <string>
#include <memory>
#include <chrono>

#include "session.hpp"
#include "buffer.hpp"

bool ExsistCheck(const std::string& topic) {
  const std::string shm_file = "/dev/shm/" + topic; 
  return access(shm_file.c_str(), F_OK ) != -1;
}

class ShmSession : public Session {
 public:
  ShmSession() : fd_(0) {}
  ~ShmSession() {}

  const size_t kDefaultMemorySize = 64 * 1024 * 1024;

  bool Open(const std::string& topic) {
    if (fd_ != 0) {
      return false;
    }

    if (!ExsistCheck(topic)) {
      return CreateSession(topic);
    } 

    return ConnetSession(topic);
  }

  void Close() {
    munmap(buffer_.get(), kDefaultMemorySize);
    buffer_.reset(nullptr);
  }

  void Write(const std::string& buf) {
    buffer_->header_.timestamp = NowTimestamp();
    buffer_->header_.timestamp = buf.size();
    std::copy(buf.begin(), buf.end(), buf.begin());
  }
  void Read() {
    
  }
 
 private:
  bool CreateSession(const std::string& topic) {
    fd_ = shm_open(topic.c_str(), O_CREAT | O_RDWR, 0600);
    if (fd_ < 0) {
      return false;
    }

    if (ftruncate(fd_, kDefaultMemorySize) == -1) {
      return false;
    }

    buffer_.reset(static_cast<Buffer*>(mmap(
      nullptr, kDefaultMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0)));
    return true;
  }
  
  bool ConnetSession(const std::string& topic) {
    fd_ = shm_open(topic.c_str(), O_CREAT | O_RDWR, 0600);
    if (fd_ < 0) {
      return false;
    }

    buffer_.reset(static_cast<Buffer*>(mmap(
      nullptr, kDefaultMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0)));
    return true;
  }
  
  void ReadHeader() {}
  
  void UpdateBuffer() {}

 private:
  int fd_;
  std::unique_ptr<Buffer> buffer_;
};

#endif // SUTILS_CHNNEL_SHARED_MEMORY_SESSION_HPP_
