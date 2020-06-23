/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_FLOATSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_FLOATSERIALIZE_HPP_

#include <type_traits>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

namespace helper {

template <typename T>
struct TypeTraits<T, typename std::enable_if<std::is_floating_point<T>::value, void>::type> {
  static constexpr bool valid = true;
  using type = T;
};

template <typename T> struct FloatTraits : public TypeTraits<T> {
  static_assert(TypeTraits<T>::valid, "T - Unsupported Type");
};

template <typename T> struct FloatTraits<T*> : public FloatTraits<T> {
  static_assert(FloatTraits<T>::valid, "T* - Unsupported Type");
};

template <typename T> struct FloatTraits<const T*> : public FloatTraits<T> {
  static_assert(FloatTraits<T>::valid, "const T* - Unsupported Type");
};

template <typename T> struct FloatTraits<T&> : public FloatTraits<T> {
  static_assert(FloatTraits<T>::valid, "T& - Unsupported Type");
};

template <typename T> struct FloatTraits<const T&> : public FloatTraits<T> {
  static_assert(FloatTraits<T>::valid, "const T& - Unsupported Type");
};

template <typename T, std::size_t N> struct FloatTraits<T[N]> : public FloatTraits<T> {
  static_assert(FloatTraits<T>::valid, "T[N] - Unsupported Type");
};

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<T, B, typename helper::FloatTraits<T>::type> {
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

#endif  // SUTILS_SERIALIZE_TYPE_FLOATSERIALIZE_HPP_
