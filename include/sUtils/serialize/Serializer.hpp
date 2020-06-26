/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_SERIALIZER_HPP_
#define SUTILS_SERIALIZE_SERIALIZER_HPP_

#include <string>

#include "type/Type.hpp"
#include "Buffer.hpp"

namespace sUtils {

class Serializer {
 public:
  Serializer() = default;
  ~Serializer() = default;

  template <typename T>
  void serialize(const T& data) {
    type::TypeSerializer<T, Buffer, T>::serialize(data, m_buf);
  }

  template <typename T>
  void deserialize(T& data) {
    type::TypeSerializer<T, Buffer, T>::deserialize(data, m_buf);
  }

  const std::string& getSerialized() {
    return m_buf.toString();
  }

 private:
  Buffer m_buf;
};

}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_SERIALIZER_HPP_
