/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_CHNNEL_SHARED_MEMORY_SESSION_HPP_
#define SUTILS_CHNNEL_SHARED_MEMORY_SESSION_HPP_

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <dirent.h>

#include <string>
#include <memory>
#include <chrono>

#include "session.hpp"
#include "buffer.hpp"

bool ExsistCheck(const std::string& topic) {
  const std::string shm_path = "/dev/shm";
  std::vector<std::string> file_list;

  DIR* dirp = opendir(shm_path.c_str());
  struct dirent * dp;

  while ((dp = readdir(dirp)) != NULL) {
    file_list.push_back(dp->d_name);
  }

  for (const std::string& file_name : file_list) {
    if (file_name.compare(topic) == 0) {
      return true;
    }
  }

  return false;
}

class ShmSession : public Session {
 public:
  enum class Mode {
    READ,
    WRITE
  };

  ShmSession() : fd_(0), shm_(nullptr), idx_(0) {}
  ~ShmSession() {}

  const size_t kDefaultMemorySize = 64 * 1024 * 1024;

  bool Open(const std::string& topic) {
    std::cout << "Open\n";
    topic_ = topic;

    if (fd_ != 0) {
      return false;
    }

    if (!ExsistCheck(topic)) {
      return CreateSession(topic);
    } 

    return ConnetSession(topic);
  }

  void Close() {
    DecreseObserve();

    if (!GetObserved()) {
      munmap(shm_, kDefaultMemorySize);
      shm_ = nullptr;
      
      shm_unlink(topic_.c_str());
    }
  }

  void Write(const std::string& buf) {
    std::vector<uint8_t> data(buf.begin(), buf.end());
    size_t len = buf.size();

    while (!shm_->TryWrite(&data[0], len, &idx_)) {}
  }

  std::string Read() {
    std::vector<uint8_t> data(1024 * 1024, 0);
    size_t len = 0;

    while (!shm_->TryRead(&data[0], &len, &idx_)) {}

    data.resize(len);
    PrintDebug(data);

    return std::move("");
  }
 
 private:
  bool CreateSession(const std::string& topic) {
    std::cout << "CreateSession\n";

    fd_ = shm_open(topic.c_str(), O_CREAT | O_RDWR, 0600);
    if (fd_ < 0) {
      return false;
    }

    if (ftruncate(fd_, kDefaultMemorySize) == -1) {
      return false;
    }

    shm_ = static_cast<Memory*>(mmap(
      nullptr, kDefaultMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));
;
    return true;
  }
  
  bool ConnetSession(const std::string& topic) {
    std::cout << "CreateSession\n";

    fd_ = shm_open(topic.c_str(), O_CREAT | O_RDWR, 0600);
    if (fd_ < 0) {
      return false;
    }

    shm_ = static_cast<Memory*>(mmap(
      nullptr, kDefaultMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));

    IncreseObserve();
    return true;
  }

  void IncreseObserve() { shm_->IncreseObserve(); }
  void DecreseObserve() { shm_->DecreseObserve(); }
  uint32_t GetObserved() const { return shm_->GetObserved(); }

  void PrintDebug(const std::vector<uint8_t>& data) {
    // std::cout << "-------------\n";
    // std::cout << "TimeStamp : " << shm_->header_.timestamp << std::endl;
    // std::cout << "len : " << shm_->header_.len << std::endl;
    // std::cout << "observed : " << shm_->header_.observed << std::endl;

    std::string tmp(data.begin(), data.end());
    std::cout << "buf : " << tmp << std::endl;
  }

 private:
  int fd_;
  std::string topic_;
  Memory* shm_;
  uint32_t idx_;
};

#endif // SUTILS_CHNNEL_SHARED_MEMORY_SESSION_HPP_
