/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_INTSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_INTSERIALIZE_HPP_

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

namespace helper {

template <typename T, typename ENABLE = void>
struct IntTraits : TypeTraits<T>{};

template <typename T>
struct IntTraits<T, typename std::enable_if<!std::is_unsigned<T>::value &&
                                            std::is_integral<T>::value>::type> {
  static constexpr bool valid = true;
  using type = T;
};

template <typename T, std::size_t N>
struct IntTraits<T[N], typename std::enable_if<std::is_array<T[N]>::value &&
                                               !std::is_unsigned<T>::value &&
                                               std::is_integral<T>::value>::type> {
  static constexpr bool valid = true;
  using type = T[N];
};

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<T, B, typename helper::IntTraits<T>::type> {
 public:
  static void serialize(const T& data, B& buf) {
    buf.write(data);
  }

  static void deserialize(T& dst, B& buf) {
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_INTSERIALIZE_HPP_
