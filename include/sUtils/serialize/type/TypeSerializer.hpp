/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
#define SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_

#include "Type.hpp"

namespace sUtils {
namespace type {

template<typename T, typename B, typename ENABLE = void>
class TypeSerializer {
 public:
  static void serialize(T& data, B& buf) {
    buf.write(data);
  }

  static void deserialize(T& dst, B& buf) {
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
