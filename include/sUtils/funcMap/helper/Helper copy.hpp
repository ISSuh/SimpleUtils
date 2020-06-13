/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_FUNCMAP_HELPER_HPP_
#define SUTILS_FUNCMAP_HELPER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <tuple>

namespace sUtils {
namespace helper {

template <size_t... Is>
struct seq {};

template <size_t N, size_t... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

template <size_t... Is>
struct gen_seq<0, Is...> : seq<Is...> {};


template <typename F, typename Tuple, size_t... N>
auto callMethod_impl(
  F f,
  Tuple&& t,
  seq<N...>) -> typename FuncTraits<F>::return_type {
    return f(ParamTraits<typename FuncTraits<F>::template argument<N>::type>::get(
            std::get<N>(std::forward<Tuple>(t)))...);
}

template <typename F, typename Tuple, size_t... N>
auto callMethod_impl(
  typename FuncTraits<F>::class_type& obj,
  F f,
  Tuple&& t,
  seq<N...>) -> typename FuncTraits<F>::return_type {
    return (obj.*f)(ParamTraits<typename FuncTraits<F>::template argument<N>::type>::get(
            std::get<N>(std::forward<Tuple>(t)))...);
}

template <typename F, typename Tuple>
auto callMethod(F f, Tuple&& t) -> typename FuncTraits<F>::return_type {
  static_assert(FuncTraits<F>::valid, "Function not usable as RPC");

  return callMethod_impl(f,
                         std::forward<Tuple>(t),
                         gen_seq<FuncTraits<F>::arity>());
}

template <typename F, typename Tuple>
auto callMethod(typename FunctionTraits<F>::class_type& obj,
                F f,
                Tuple&& t) -> typename FuncTraits<F>::return_type {
  static_assert(FunctionTraits<F>::valid, "Function not usable as RPC");

  return callMethod_impl(obj,
                         f,
                         std::forward<Tuple>(t),
                         gen_seq<FuncTraits<F>::arity>());
}

//////////////////////////////////////////////////

}  // namespace helper
}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_HELPER_HPP_
