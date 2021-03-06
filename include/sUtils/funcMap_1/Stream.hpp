/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_FUNCMAP_STREAM_HPP_
#define SUTILS_FUNCMAP_STREAM_HPP_

#pragma once

#include <vector>
#include <utility>

#include "helper/Helper.hpp"

namespace sUtils {
namespace stream {

class Stream {
 public:
  Stream() {}
  explicit Stream(std::vector<char> data) : m_buf(std::move(data)) {}

  void clear() {
    m_buf.clear();
    m_readpos = 0;
  }

  void write(const void* src, int size) {
    auto p = reinterpret_cast<const char*>(src);
    m_buf.insert(m_buf.end(), p, p + size);
  }

  void read(void* dst, int size) {
    auto p = reinterpret_cast<char*>(dst);
    memcpy(p, &m_buf[m_readpos], size);
    m_readpos += size;
  }

  int readSize() const {
    return static_cast<int>(m_buf.size()) - m_readpos;
  }

  int writeSize() const {
    return static_cast<int>(m_buf.size());
  }

  std::vector<char> extract() {
    m_readpos = 0;
    return std::move(m_buf);
  }

  char* ptr(int index) {
    return &m_buf[index];
  }

 private:
  std::vector<char> m_buf;
  int m_readpos = 0;
};

template <typename T>
Stream& operator<<(Stream& s, const T& v) {
  helper::TypeTraits<T>::write(s, v);
  return s;
}

template <typename T>
Stream& operator>>(Stream& s, T& v) {
  helper::TypeTraits<T>::read(s, v);
  return s;
}

}  // namespace stream
}  // namespace sUtils


#endif  // SUTILS_FUNCMAP_STREAM_HPP_
