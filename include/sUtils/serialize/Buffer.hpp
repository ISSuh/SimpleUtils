/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_BUFFER_HPP_
#define SUTILS_SERIALIZE_BUFFER_HPP_

#include <string>
#include <vector>
#include <algorithm>

#include "type/TypeSerializer.hpp"

namespace sUtils {

class Buffer {
 public:
  Buffer() : m_head(0) {}
  explicit Buffer(size_t size) : m_buf(std::vector<uint8_t>(size)), m_head(0) {}
  ~Buffer() {
    clear();
  }

  template<typename T>
  void write(const T& value) {
    size_t size = sizeof(value);
    m_buf.insert(m_buf.end(), size, value);
  }

  template<typename T>
  void read(void* dst) {
    size_t size = sizeof(dst);

    std::copy(m_buf[m_head], m_buf[m_head + size], dst);
    m_head += size;
  }

  void clear() {
    m_buf.clear();
    m_head = 0;
  }

  const std::string& toString() {
    return std::string(m_buf.begin(), m_buf.end());
  }

  void fromString(const std::string& serializedValue) {
  }

  template<typename T>
  Buffer& operator<<(const T& rhs) {
    type::TypeSerializer<T, Buffer>::serialize(rhs, *this);
    return *this;
  }

  template<typename T>
  Buffer& operator>>(const T& rhs) {
    type::TypeSerializer<T, Buffer>::deserialize(rhs, *this);
    return *this;
  }

 private:
  std::vector<uint8_t> m_buf;
  uint32_t m_head;
};

}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_BUFFER_HPP_
