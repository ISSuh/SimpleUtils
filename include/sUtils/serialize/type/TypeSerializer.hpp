/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
#define SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_

#include <iostream>
#include <typeinfo>

namespace sUtils {
namespace type {

template<typename T, typename B, typename ENABLE = void>
class TypeSerializer {
 public:
  static void serialize(const T& data, B& buf) {
    std::cout << "BASE\n";
    buf.write(data);
  }

  static void deserialize(T& dst, B& buf) {
    std::cout << "BASE\n";
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_TYPESERIALIZER_HPP_
