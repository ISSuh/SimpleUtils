/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_STRINGSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_STRINGSERIALIZE_HPP_

#include <string>
#include <cstring>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

template<typename B>
class TypeSerializer<std::string, B> {
 public:
  static void serialize(const std::string& data, B& buf) {
    buf.write(data.data(), data.length());
  }

  static void deserialize(std::string& dst, B& buf) {
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_STRINGSERIALIZE_HPP_
