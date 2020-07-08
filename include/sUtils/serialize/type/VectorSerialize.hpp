/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_VECTORSERIALIZE_HPP_
#define SUTILS_SERIALIZE_TYPE_VECTORSERIALIZE_HPP_

#include <vector>

#include "helper/TypeTrait.hpp"
#include "TypeSerializer.hpp"

namespace sUtils {
namespace type {

namespace helper {

template <typename T>
using is_vector = std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>;

template <typename T, typename ENABLE = void>
struct VectorTraits : TypeTraits<T> {};

template <typename T>
struct VectorTraits<T, typename std::enable_if<is_vector<T>::value>::type> {
  static constexpr bool valid = true;
  using type = typename std::enable_if<is_vector<T>::value>::type;
};

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<T, B, typename helper::VectorTraits<T>::type> {
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

#endif  // SUTILS_SERIALIZE_TYPE_VECTORSERIALIZE_HPP_
