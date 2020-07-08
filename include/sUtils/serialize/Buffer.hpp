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

#include "type/helper/Common.hpp"
#include "type/TypeSerializer.hpp"

namespace sUtils {

class Buffer {
 public:
  Buffer() : m_argCount(0), m_argHead(-1)  {}
  ~Buffer() { clear(); }

  template<typename T>
  void write(const T& value) {
    size_t size = sizeof(value);
    write(value, size);
  }

  template<typename T>
  void write(const T& value, size_t len) {
    const char* p = reinterpret_cast<const char*>(&value);
    std::copy(p, p + len, std::back_inserter(m_buf));

    writeBufferByteInfo(len);
  }

  template<typename T>
  void read(T& dst) {
    auto beginBytePos = m_byteRange.front().first;
    auto endBytePos = m_byteRange.front().second;

    std::copy(&m_buf[beginBytePos], &m_buf[endBytePos] + 1, reinterpret_cast<char*>(&dst));

    readBufferByteInfo();
  }

  void clear() {
    m_buf.clear();

    clearBufferByteInfo();
  }

  const std::string& toString() { return std::move(std::string(m_buf.begin(), m_buf.end())); }

  size_t size() const { return m_buf.size(); }
  size_t count() const { return m_argCount; }
  const buffer::ByteRangeVector& getAllByteInfo() const { return m_byteRange; }
  std::pair<size_t, size_t> getByteInfo() const {
    if (m_argCount <= 0) {
      return {-1, -1};
    }

    return m_byteRange[m_argHead];
  }

 private:
  void writeBufferByteInfo(size_t len) {
    auto nextBytePos = m_argCount == 0 ? 0 : m_byteRange.back().second + 1;

    m_byteRange.emplace_back(std::make_pair(nextBytePos, nextBytePos + len - 1));

    ++m_argHead;
    ++m_argCount;
  }

  void readBufferByteInfo() {
    if (!m_byteRange.empty()) {
      m_byteRange.erase(m_byteRange.begin());
    }

    --m_argHead;
    --m_argCount;

    if (!m_argCount) {
      clear();
    }
  }

  void clearBufferByteInfo() {
    m_byteRange.clear();

    m_argHead = -1;
    m_argCount = 0;
  }

 private:
  std::vector<char> m_buf;

  buffer::ByteRangeVector m_byteRange;
  size_t m_argCount;
  int32_t m_argHead;
};

template<>
inline void Buffer::write(const std::string& value, size_t len) {
  const char* p = value.c_str();
  std::copy(p, p + len, std::back_inserter(m_buf));

  writeBufferByteInfo(len);
}

template<>
inline void Buffer::read(std::string& dst) {
  auto beginBytePos = m_byteRange.front().first;
  auto endBytePos = m_byteRange.front().second;

  std::copy(&m_buf[beginBytePos], &m_buf[endBytePos] + 1, std::back_inserter(dst));

  readBufferByteInfo();
}

}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_BUFFER_HPP_
