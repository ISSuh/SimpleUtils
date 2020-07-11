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

// template <typename T>
// using is_vector = std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>;

// template <typename T, typename ENABLE = void>
// struct VectorTraits : TypeTraits<T> {};

// template <typename T>
// struct VectorTraits<T, typename std::enable_if<is_vector<T>::value>::type> {
//   static constexpr bool valid = true;
//   using type = typename std::enable_if<is_vector<T>::value>::type;
// };

}  // namespace helper

template<typename T, typename B>
class TypeSerializer<std::vector<T>, B> {
 public:
  static void serialize(const std::vector<T>& data, B& buf) {
    for (const auto& val : data) {
      TypeSerializer<T, B>::serialize(val, buf);
    }
  }

  static void deserialize(std::vector<T>& dst, B& buf) {
    buf.read(dst);
  }
};

template<typename B>
class TypeSerializer<std::vector<std::string>, B> {
 public:
  static void serialize(const std::vector<std::string>& data, B& buf) {
    for (const auto& val : data) {
      TypeSerializer<std::string, B>::serialize(val, buf);
    }
  }

  static void deserialize(std::vector<std::string>& dst, B& buf) {
    
    buf.read(dst);
  }
};

}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_VECTORSERIALIZE_HPP_
