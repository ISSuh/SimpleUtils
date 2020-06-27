/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_BUFFER_HPP_
#define SUTILS_SERIALIZE_BUFFER_HPP_

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

#include "type/TypeSerializer.hpp"

namespace sUtils {

class Buffer {
 public:
  Buffer() : m_head(0) {}
  explicit Buffer(size_t size) : m_buf(std::vector<char>(size)),
                                 m_head(0),
                                 m_argCount(0),
                                 m_argHead(-1) {}
  ~Buffer() {
    clear();
  }

  template<typename T>
  void write(const T& value) {
    size_t size = sizeof(value);
    write(value, size);
  }

  template<typename T>
  void write(const T& value, size_t len) {
    const char* p = reinterpret_cast<const char*>(&value);
    std::copy(p, p + len, std::back_inserter(m_buf));

    updateBufferByteInfo(len);
  }

  template<typename T>
  void read(T& dst) {
    size_t size = sizeof(dst);
    read(dst, size);
  }

  template<typename T>
  void read(T& dst, size_t len) {
    if (m_head + len > static_cast<uint32_t>(m_buf.size())) {
      throw "Out of Range";
    }

    std::copy(&m_buf[m_head], &m_buf[m_head] + len,
              reinterpret_cast<char*>(&dst));
    m_head += size;

    updateBufferByteInfo();
  }

  void clear() {
    m_buf.clear();
    m_head = 0;

    clearBufferByteInfo();
  }

  const std::string& toString() {
    return std::move(std::string(m_buf.begin(), m_buf.end()));
  }

  void fromString(const std::string& serializedValue) {
    write(serializedValue);
  }

  const size_t getCount() const { return m_argCount; }

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
  void updateBufferByteInfo(size_t len) {
    auto nextBytePos = m_argCount == 0 ? 0 : m_argByteRange[m_argHead].second + 1;

    m_argByteRange.emplace(std::make_pair(nextBytePos, nextBytePos + len));

    ++m_argHead;
    ++m_argCount;
  }

  void updateBufferByteInfo() {
    m_argByteRange.pop();
    --m_argHead;
    --m_argCount;
  }

  void clearBufferByteInfo() {
    m_argByteRange.clear();
    m_argHead = -1;
    m_argCount = 0;
  }

 private:
  std::vector<char> m_buf;
  uint32_t m_head;

  std::queue<std::pair<size_t, size_t>> m_argByteRange;
  size_t m_argCount;
  int32_t m_argHead;
};

}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_BUFFER_HPP_
