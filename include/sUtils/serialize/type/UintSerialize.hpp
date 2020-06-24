/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_UINTSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_UINTSERIALIZE_HPP_

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

namespace helper {

template <typename T>
struct TypeTraits<T, typename std::enable_if<(std::is_unsigned<T>::value), void>::type> {
  static constexpr bool valid = true;
  using type = T;
};

template <typename T>
struct TypeTraits<T, typename std::enable_if<(std::is_array<T>::value &&
                                              std::is_unsigned<T>::value), void>::type> {
  static constexpr bool valid = true;
  using type = T;
};

template <typename T> struct UintTraits : public TypeTraits<T> {
  static_assert(TypeTraits<T>::valid, "UintTraits: T - Unsupported Type");
};

template <typename T> struct UintTraits<T*> : public UintTraits<T> {
  static_assert(UintTraits<T>::valid, "UintTraits: T* - Unsupported Type");
};

template <typename T> struct UintTraits<const T*> : public UintTraits<T> {
  static_assert(UintTraits<T>::valid, "UintTraits: const T* - Unsupported Type");
};

template <typename T> struct UintTraits<T&> : public UintTraits<T> {
  static_assert(UintTraits<T>::valid, "UintTraits: T& - Unsupported Type");
};

template <typename T> struct UintTraits<const T&> : public UintTraits<T> {
  static_assert(UintTraits<T>::valid, "UintTraits: const T& - Unsupported Type");
};

template <typename T, int N> struct UintTraits<T[N]> : public UintTraits<T> {
  static_assert(UintTraits<T>::valid, "UintTraits: T[N] - Unsupported Type");
};

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<T, B, typename helper::UintTraits<T>::type> {
 public:
  static void serialize(T& data, B& buf) {
    std::cout << "UINT\n";
    buf.write(data);
  }

  static void deserialize(T& dst, B& buf) {
    std::cout << "UINT\n";
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_UINTSERIALIZE_HPP_
