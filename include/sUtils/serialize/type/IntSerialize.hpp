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
struct IntTraits<T, typename std::enable_if<std::is_signed<T>::value &&
                                            std::is_integral<T>::value>::type> {
  static constexpr bool valid = true;
  using type = typename std::enable_if<std::is_signed<T>::value &&
                                            std::is_integral<T>::value>::type;
};

template <typename T, std::size_t N>
struct IntTraits<T[N], typename std::enable_if<std::is_array<T[N]>::value &&
                                               std::is_signed<T>::value &&
                                               std::is_integral<T>::value>::type> {
  static constexpr bool valid = true;
  using type = typename std::enable_if<std::is_array<T[N]>::value &&
                                               std::is_signed<T>::value &&
                                               std::is_integral<T>::value>::type;
};

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<T, B, typename helper::IntTraits<T>::type> {
 public:
  static void serialize(const T& data, B& buf) {
    std::cout << "int\n";
    buf.write(data);
  }

  static void deserialize(T& dst, B& buf) {
    std::cout << "int\n";
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_INTSERIALIZE_HPP_
