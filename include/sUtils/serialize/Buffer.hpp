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
  Buffer() : m_argCount(0), m_argHead(-1)  {}
  explicit Buffer(size_t size) : m_buf(std::vector<char>(size)),
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
    if (len > static_cast<uint32_t>(m_buf.size())) {
      throw "Out of Range";
    }

    auto beginBytePos = m_argByteRange.front().first;
    auto endBytePos = m_argByteRange.front().second;

    std::copy(&m_buf[beginBytePos], &m_buf[endBytePos] + 1, reinterpret_cast<char*>(&dst));

    updateBufferByteInfo();
  }

  void clear() {
    m_buf.clear();

    clearBufferByteInfo();
  }

  const std::string& toString() {
    return std::move(std::string(m_buf.begin(), m_buf.end()));
  }

  void fromString(const std::string& serializedValue) {
    write(serializedValue);
  }

  size_t getCount() const { return m_argCount; }

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
    auto nextBytePos = m_argCount == 0 ? 0 : m_argByteRange.back().second + 1;

    m_argByteRange.emplace(std::make_pair(nextBytePos, nextBytePos + len - 1));

    ++m_argHead;
    ++m_argCount;
  }

  void updateBufferByteInfo() {
    m_argByteRange.pop();
    --m_argHead;
    --m_argCount;

    if (!m_argCount) {
      clear();
    }
  }

  void clearBufferByteInfo() {
    std::queue<std::pair<size_t, size_t>> empty;
    std::swap(m_argByteRange, empty);

    m_argHead = -1;
    m_argCount = 0;
  }

 private:
  std::vector<char> m_buf;

  std::queue<std::pair<size_t, size_t>> m_argByteRange;
  size_t m_argCount;
  int32_t m_argHead;
};

template<>
void Buffer::write(const std::string& value, size_t len) {
  const char* p = value.c_str();
  std::copy(p, p + len, std::back_inserter(m_buf));

  updateBufferByteInfo(len);
}

template<>
inline void Buffer::read(std::string& dst, size_t len) {
  if (len > static_cast<uint32_t>(m_buf.size())) {
    throw "Out of Range";
  }

  auto beginBytePos = m_argByteRange.front().first;
  auto endBytePos = m_argByteRange.front().second + 1;

  std::copy(&m_buf[beginBytePos], &m_buf[endBytePos], std::back_inserter(dst));

  updateBufferByteInfo();
}

}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_BUFFER_HPP_
