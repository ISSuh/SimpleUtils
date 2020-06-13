/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_FUNCMAP_HELPER_FUNCTRAITS_HPP_
#define SUTILS_FUNCMAP_HELPER_FUNCTRAITS_HPP_

#include <utility>
#include <tuple>

#include "TypeTraits.hpp"

namespace sUtils {
namespace helper {

/**
 * Function Parameter Traits
 */

template <typename... T>
struct ParamPackTraits {
  static constexpr bool valid = true;
};

template <typename First>
struct ParamPackTraits<First> {
  static constexpr bool valid = TypeTraits<First>::valid;
};

template <typename First, typename... Rest>
struct ParamPackTraits<First, Rest...> {
  static constexpr bool valid = (TypeTraits<First>::valid && ParamPackTraits<Rest...>::valid);
};

/**
 * Funtion Traits
 */

template <typename F> struct FuncTraits {};

// function
template <typename R, typename... Args>
struct FuncTraits<R(*)(Args...)> : public FuncTraits<R(Args...)> {};

// class member method pointer
template <typename R, typename C, typename... Args>
struct FuncTraits<R (C::*)(Args...)> : public FuncTraits<R(Args...)> {
  using class_type = C;
};

// const class member method pointer
template <typename R, typename C, typename... Args>
struct FuncTraits<R (C::*)(Args...) const> : public FuncTraits<R(Args...)> {
  using class_type = C;
};

// const method pointer
template <typename R, typename... Args>
struct FuncTraits<R(Args...)> {
  using return_type = R;
  static constexpr bool valid =
      (TypeTraits<return_type>::valid && ParamPackTraits<Args...>::valid);

  using param_tuple = std::tuple<typename TypeTraits<Args>::store_type...>;
  static constexpr std::size_t arg_count = sizeof...(Args);

  template <std::size_t N>
  struct argument {
    static_assert(N < arg_count, "error: invalid parameter index.");

    using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
  };
};

// lambda fucntion
template <typename T>
struct FunctionTraits : public FuncTraits<decltype(&T::operator())> {};

}  // namespace helper
}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_HELPER_FUNCTRAITS_HPP_
