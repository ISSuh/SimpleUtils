/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_SERIALIZE_HPP_
#define SUTILS_SERIALIZE_SERIALIZE_HPP_

namespace sUtils {

class Serialization {
 public:
  Serialization() = default;
  ~Serialization() = default;

  void serialize();
  void deserialize();
};

}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_SERIALIZE_HPP_
