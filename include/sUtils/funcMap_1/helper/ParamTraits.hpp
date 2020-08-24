/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_FUNCMAP_HELPER_PARAMTRAITS_HPP_
#define SUTILS_FUNCMAP_HELPER_PARAMTRAITS_HPP_

#include <iostream>
#include <utility>
#include <tuple>

#include "TypeTraits.hpp"
#include "FuncTraits.hpp"

namespace sUtils {
namespace helper {

/**
 * Tuple Traits
 */

template <typename T, bool Done, int N>
struct Tuple {
  template <typename S>
  static void deserialize(S& s, T& v) {
    s >> std::get<N>(v);
    Tuple<T, N == std::tuple_size<T>::value - 1, N + 1>::deserialize(s, v);
  }

  template <typename S>
  static void serialize(S& s, const T& v) {
    s << std::get<N>(v);
    Tuple<T, N == std::tuple_size<T>::value - 1, N + 1>::serialize(s, v);
  }
};

template <typename T, int N>
struct Tuple<T, true, N> {
  template <typename S>
  static void deserialize(S&, T&) {}

  template <typename S>
  static void serialize(S&, const T&) {}
};

/**
 * serialize
 */

struct ParamPack {
  template <typename S>
  static void serialize(S&) {}

  template <typename S, typename First, typename... Rest>
  static void serialize(S& s, First&& first, Rest&&... rest) {
    using Traits = TypeTraits<First>;
    Traits::write(s, std::forward<First>(first));
    ParamPack::serialize(s, std::forward<Rest>(rest)...);
  }
};

template <typename F, int N>
struct Parameters : public ParamPack {
  template <typename S>
  static void serialize(S&) {}

  template <typename S, typename First, typename... Rest>
  static void serialize(S& s, First&& first, Rest&&... rest) {
    using Traits = TypeTraits<typename FuncTraits<F>::template argument<N>::type>;
    Traits::write(s, std::forward<First>(first));
    Parameters<F, N + 1>::serialize(s, std::forward<Rest>(rest)...);
  }
};

/**
 * deserialize
 */

template <typename... T>
struct TypeTraits<std::tuple<T...>> {
  using tuple_type = std::tuple<T...>;
  using store_type = tuple_type;
  static constexpr bool valid = ParamPackTraits<T...>::valid;

  static_assert(ParamPackTraits<T...>::valid == true,
              "One or more tuple elements are not of valid RPC parameter types.");

  template <typename S>
  static void write(S& s, const tuple_type& v) {
    Tuple<tuple_type, std::tuple_size<tuple_type>::value == 0, 0>::serialize(s, v);
  }

  template <typename S>
  static void read(S& s, tuple_type& v) {
    Tuple<tuple_type, std::tuple_size<tuple_type>::value == 0, 0>::deserialize(s, v);
  }

  static tuple_type&& get(tuple_type&& v) { return std::move(v); }
};

}  // namespace helper
}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_HELPER_PARAMTRAITS_HPP_
