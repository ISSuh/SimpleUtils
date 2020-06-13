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

struct return_void {};
struct return_non_void{};
struct arg_count_zero{};
struct arg_count_non_zero{};

template<typename R>
struct FunctReturnTrait {
  using type = return_non_void;
};

template<>
struct FunctReturnTrait<void> {
  using type = return_void;
};

template<int n>
struct FunctArgsTrait {
  using type = arg_count_non_zero;
};

template<>
struct FunctArgsTrait<0> {
  using type = arg_count_zero;
};

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
struct FuncTraits<R(Args...)> {
  using return_type = R;
  using return_type_info = typename FunctReturnTrait<return_type>::type;

  static constexpr std::size_t arg_count = sizeof...(Args);
  using arg_count_info = typename FunctArgsTrait<arg_count>::type;

  using param_tuple = std::tuple<typename TypeTraits<Args>::store_type...>;
  static constexpr bool valid =
      (TypeTraits<return_type>::valid && ParamPackTraits<Args...>::valid);

  template <std::size_t N>
  struct argument {
    static_assert(N < arg_count, "error: invalid parameter index.");

    using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
  };
};

// function pointer
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

// lambda fucntion
template <typename T>
struct FunctionTraits : public FuncTraits<decltype(&T::operator())> {};

}  // namespace helper
}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_HELPER_FUNCTRAITS_HPP_
