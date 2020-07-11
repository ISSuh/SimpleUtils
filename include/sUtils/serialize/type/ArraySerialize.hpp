/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_ARRAYSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_ARRAYSERIALIZE_HPP_

#include <array>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

namespace helper {

// template <typename T>
// using is_array = std::is_same<T, std::array<typename T::value_type, 0>>;

// template <typename T, typename ENABLE = void>
// struct ArrayTraits : TypeTraits<T> {};

// template <typename T>
// struct ArrayTraits<T, typename std::enable_if<is_array<T>::value>::type> {
//   static constexpr bool valid = true;
//   using type = typename std::enable_if<is_array<T>::value>::type;
// };

}  // namespace helper

template<typename T, typename B, size_t N>
class TypeSerializer<std::array<T, N>, B> {
 public:
  static void serialize(const std::array<T, N>& data, B& buf) {
    std::cout << "array contailner\n";
    buf.write(data);
  }

  static void deserialize(std::array<T, N>& dst, B& buf) {
    std::cout << "array contailner\n";
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_ARRAYSERIALIZE_HPP_
