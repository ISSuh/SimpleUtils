/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_SERIALIZE_TYPE_HELPER_COMMON_HPP_
#define SUTILS_SERIALIZE_TYPE_HELPER_COMMON_HPP_

#include <type_traits>

namespace sUtils {
namespace type {
namespace helper {

template<typename... Arg>
void UNUSE(Arg&&...) {}

}  // namespace helper
}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_HELPER_COMMON_HPP_
