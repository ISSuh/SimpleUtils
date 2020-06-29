/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_STRINGSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_STRINGSERIALIZE_HPP_

#include <string>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

template<typename T, typename B>
class TypeSerializer<T, B, std::string> {
 public:
  static void serialize(const T& data, B& buf) {
    buf.write(data, data.length());
  }

  static void deserialize(T& dst, B& buf) {
    buf.read(dst, dst.length());
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_STRINGSERIALIZE_HPP_
