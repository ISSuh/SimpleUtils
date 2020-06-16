/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_BUFFER_BUFFER_HPP_
#define SUTILS_SERIALIZE_BUFFER_BUFFER_HPP_

#include <vector>

namespace sUtils {
namespace buffer {

class Buffer {
 public:
  Buffer() = default;
  ~Buffer() = default;

 private:
  std::vector<char> m_buf;
};

}  // namespace buffer
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_BUFFER_BUFFER_HPP_
