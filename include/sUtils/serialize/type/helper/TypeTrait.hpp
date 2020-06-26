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

template <typename T, typename ENABLE = void> struct TypeTraits {};

template<typename C> struct is_char : std::integral_constant<bool, std::is_same<C, char>::value ||
                                                                   std::is_same<C, char16_t>::value ||
                                                                   std::is_same<C, char32_t>::value ||
                                                                   std::is_same<C, wchar_t>::value> {};

}  // namespace helper
}  // namespace type
}  // namespace sUtils

#endif  // SUTILS_SERIALIZE_TYPE_HELPER_TYPETRAIT_HPP_
