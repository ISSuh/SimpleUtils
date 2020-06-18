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
  template <typename Type>
  static void serialize(Type data) {
    m_buf.write(data);
  }

  template <typename Type>
  static void serialize(Type* data) {
    m_buf.write(*data);
  }

  template <typename Type>
  static void serialize(Type& data) {
    m_buf.write(data);
  }

  template <typename Type>
  static void deserialize(Type& data) {
    m_buf.read(data);
  }

 private:
  helper::Buffer m_buf;
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
