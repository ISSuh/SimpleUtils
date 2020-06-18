/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_SERIALIZER_HPP_
#define SUTILS_SERIALIZE_SERIALIZER_HPP_

#include "type/Type.hpp"
#include "buffer/Buffer.hpp"

namespace sUtils {

class Serializer {
 public:
  Serializer() = default;
  ~Serializer() = default;

  template <typename Type>
  static void serialize(Type data);

  template <typename Type>
  static void serialize(Type* data, int size);

  template <typename Type>
  static void deserialize(Type data, int size);
};

}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_SERIALIZER_HPP_
