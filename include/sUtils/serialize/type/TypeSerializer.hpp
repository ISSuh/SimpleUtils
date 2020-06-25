/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
#define SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_

#include "helper/Common.hpp"

namespace sUtils {
namespace type {

template<typename T, typename B, typename ENABLE = void>
class TypeSerializer {
 public:
  static void serialize(T& data, B& buf) { helper::UNUSE(data, buf); }

  static void deserialize(T& dst, B& buf) { helper::UNUSE(dst, buf); }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
