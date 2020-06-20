/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_UINTSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_UINTSERIALIZE_HPP_

#include <type_traits>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

namespace helper {

template <typename T>
struct TypeTraits<T,
                  typename std::enable_if<std::is_arithmetic<T>::value &&
                                          std::is_unsigned<T>::value
                                         >::type> {
  static constexpr bool valid = true;
  using type = T;
};

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<T, B,
                     typename std::enable_if<helper::TypeTraits<T>::valid>::type
                    > {
 public:
  static void serialize(T& data, B& buf) {
    buf.write(data);
  }

  static void deserialize(T& dst, B& buf) {
    buf.read(&dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_UINTSERIALIZE_HPP_
