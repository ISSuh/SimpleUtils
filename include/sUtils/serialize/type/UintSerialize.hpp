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
  using Type = T;

  template<typename S>
  static void serialize(S& serializer, T val) { serializer.serialize(v); }

  template<typename S>
  static void deserialize(S& serializer, T val) { serializer.deserialize(v); }
};

}  // namespace helper

template<>
class Serializer {

};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_UINTSERIALIZE_HPP_
