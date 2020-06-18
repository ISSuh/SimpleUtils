/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
#define SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_

#include "type/Type.hpp"
#include "helper/Buffer.hpp"

namespace sUtils {
namespace type {

template<typename T>
class TypeSerializer {
  static void serialize(T data) {
    m_buf.write(data);
  }

  static void serialize(T* data) {
    m_buf.write(*data);
  }

  static void serialize(T& data) {
    m_buf.write(data);
  }

  static void deserialize(T& data) {
    m_buf.read(data);
  }

  TypeSerializer& operator<<(const T& rhs) {
    serialize(rhs);
    return *this;
  }

  TypeSerializer& operator>>(const T& rhs) {
    deserialize(rhs);
    return *this;
  }

 private:
  helper::Buffer m_buf;
};

template<typename T>


}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
