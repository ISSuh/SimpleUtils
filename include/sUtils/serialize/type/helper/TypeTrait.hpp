/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_HELPER_TYPETRAIT_HPP_
#define SUTILS_SERIALIZE_TYPE_HELPER_TYPETRAIT_HPP_

#include <type_traits>

namespace sUtils {
namespace type {
namespace helper {

template <typename T, typename ENABLE = void>
struct TypeTraits {
  static constexpr bool valid = false;
  using Type = T;
};

template <typename T>
struct TypeTraits<T, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
  static constexpr bool valid = true;
  using Type = T;

  template<typename S>
  static void serialize(S& serializer, T val) { serializer.serialize(v); }
};

// template <typename T> struct TypeTraits<T&> : TypeTraits<T> {
//   static_assert(TypeTraits<T>::valid, "T& - Unsupported Type");
// };

// template <typename T> struct TypeTraits<const T&> : TypeTraits<T> {
//   static_assert(TypeTraits<T>::valid, "const T& - Unsupported Type");
// };

// template <typename T> struct TypeTraits<T*> : TypeTraits<T> {
//   static_assert(TypeTraits<T>::valid, "T* - Unsupported Type");
// };

// template <typename T> struct TypeTraits<const T*> : TypeTraits<T> {
//   static_assert(TypeTraits<T>::valid, "const T* - Unsupported Type");
// };

// template <typename T> struct TypeTraits<T* const> : TypeTraits<T> {
//   static_assert(TypeTraits<T>::valid, "T* const - Unsupported Type");
// };

// template <typename T> struct TypeTraits<const T* const> : TypeTraits<T> {
//   static_assert(TypeTraits<T>::valid, "const T* const - Unsupported Type");
// };

}  // namespace helper
}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_HELPER_TYPETRAIT_HPP_
