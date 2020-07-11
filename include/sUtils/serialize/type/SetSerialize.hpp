/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_SETSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_SETSERIALIZE_HPP_

#include <set>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

template<typename T, typename B>
class TypeSerializer<std::set<T>, B> {
 public:
  static void serialize(const std::set<T>& data, B& buf) {
    std::cout << "set contailner\n";
    buf.write(data);
  }

  static void deserialize(std::set<T>& dst, B& buf) {
    std::cout << "set contailner\n";
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_SETSERIALIZE_HPP_
