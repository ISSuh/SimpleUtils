/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_FLOATSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_FLOATSERIALIZE_HPP_

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

namespace helper {

template <typename T, typename ENABLE = void>
struct FloatTraits : TypeTraits<T>{};

template <typename T>
struct FloatTraits<T, typename std::enable_if<std::is_floating_point<T>::value, void>::type> {
  static constexpr bool valid = true;
  using type = typename std::enable_if<std::is_floating_point<T>::value, void>::type;
};

template <typename T, std::size_t N>
struct FloatTraits<T[N], typename std::enable_if<std::is_array<T[N]>::value &&
                                                std::is_floating_point<T>::value, void>::type> {
  static constexpr bool valid = true;
  using type = typename std::enable_if<std::is_array<T[N]>::value &&
                                                std::is_floating_point<T>::value, void>::type;
};

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<T, B, typename helper::FloatTraits<T>::type> {
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

#endif  // SUTILS_SERIALIZE_TYPE_FLOATSERIALIZE_HPP_
