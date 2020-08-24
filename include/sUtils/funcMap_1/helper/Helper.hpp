/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_FUNCMAP_HELPER_HELPER_HPP_
#define SUTILS_FUNCMAP_HELPER_HELPER_HPP_

#include <utility>

#include "TypeTraits.hpp"
#include "FuncTraits.hpp"
#include "ParamTraits.hpp"

namespace sUtils {
namespace helper {

/**
 * Parameter Sequence
 */

template <size_t... Is>
struct seq {};

template <size_t N, size_t... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

template <size_t... Is>
struct gen_seq<0, Is...> : seq<Is...> {};

/**
 * Caller Impl
 */

template <typename F>
auto callMethod_noArg_impl(F f) -> typename FuncTraits<F>::return_type {
    return f();
}

template <typename F, typename Tuple, size_t... N>
auto callMethod_impl(
  F f,
  Tuple&& t,
  seq<N...>) -> typename FuncTraits<F>::return_type {
    return f(TypeTraits<typename FuncTraits<F>::template argument<N>::type>::get(
            std::get<N>(std::forward<Tuple>(t)))...);
}

template <typename F, typename Tuple, size_t... N>
auto callMethod_impl(
  typename FuncTraits<F>::class_type& obj,
  F f,
  Tuple&& t,
  seq<N...>) -> typename FuncTraits<F>::return_type {
    return (obj.*f)(TypeTraits<typename FuncTraits<F>::template argument<N>::type>::get(
            std::get<N>(std::forward<Tuple>(t)))...);
}

/**
 * Caller
 */

// no parameter function
template <typename F>
auto callMethod_noArg(F f) -> typename FuncTraits<F>::return_type {
  static_assert(FuncTraits<F>::valid, " no args -  Unsupport this function");

  return callMethod_noArg_impl(f);
}

// function
template <typename F, typename Tuple>
auto callMethod(F f, Tuple&& t) -> typename FuncTraits<F>::return_type {
  static_assert(FuncTraits<F>::valid, "args -  Unsupport this function");

  return callMethod_impl(f,
                         std::forward<Tuple>(t),
                         gen_seq<FuncTraits<F>::arg_count>());
}

// class member function
template <typename F, typename Tuple>
auto callMethod(typename FunctionTraits<F>::class_type& obj,
                F f,
                Tuple&& t) -> typename FuncTraits<F>::return_type {
  static_assert(FuncTraits<F>::valid, "class member  -  Unsupport this function");

  return callMethod_impl(obj,
                         f,
                         std::forward<Tuple>(t),
                         gen_seq<FuncTraits<F>::arg_count>());
}

}  // namespace helper
}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_HELPER_HELPER_HPP_
