/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_MAPSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_MAPSERIALIZE_HPP_

#include <map>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

template<typename K, typename V, typename B>
class TypeSerializer<std::map<K, V>, B> {
 public:
  static void serialize(const std::map<K, V>& data, B& buf) {
    std::cout << "map contailner\n";
    buf.write(data);
  }

  static void deserialize(std::map<K, V>& dst, B& buf) {
    std::cout << "map contailner\n";
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_MAPSERIALIZE_HPP_
