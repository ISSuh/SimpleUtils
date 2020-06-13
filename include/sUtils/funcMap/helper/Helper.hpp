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

//////////////////////////////////////////////////

template <size_t... Is>
struct seq {};

template <size_t N, size_t... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

template <size_t... Is>
struct gen_seq<0, Is...> : seq<Is...> {};

//////////////////////////////////////////////////
// Type Traits

// By default all types are invalid
template <typename T, typename ENABLE = void>
struct ParamTraits {
  static constexpr bool valid = false;
  using store_type = int;
};

template <>
struct ParamTraits<void> {
    static constexpr bool valid = true;
	using store_type = void;
};

// Support for any arithmetic type
template <typename T>
struct ParamTraits<T,
                   typename std::enable_if<std::is_arithmetic<T>::value>::type
                  > {
  static constexpr bool valid = true;
  using store_type = T;

  template <typename S>
  static void write(S& s, T v) { s.write(&v, sizeof(v)); }

  template <typename S>
  static void read(S& s, store_type& v) { s.read(&v, sizeof(v)); }

  static store_type get(store_type v) { return v; }
};

// Generic support for const T&, for any valid T
template <typename T> struct ParamTraits<T&> : ParamTraits<T> {
  static_assert(ParamTraits<T>::valid, "Invalid RPC parameter type");
};

template <typename T> struct ParamTraits<const T&> : ParamTraits<T> {
  static_assert(ParamTraits<T>::valid, "Invalid RPC parameter type");
};

template <typename T> struct ParamTraits<T*> : ParamTraits<T> {
  static_assert(ParamTraits<T>::valid, "Invalid RPC parameter type");
};

template <typename T>
struct ParamTraits<const T*> : ParamTraits<T> {
  static_assert(ParamTraits<T>::valid, "Invalid RPC parameter type");
};

template <typename T> struct ParamTraits<T* const> : ParamTraits<T> {
  static_assert(ParamTraits<T>::valid, "Invalid RPC parameter type");
};

template <typename T>
struct ParamTraits<std::vector<T>> {
  using store_type = std::vector<T>;
  static constexpr bool valid = ParamTraits<T>::valid;
  static_assert(ParamTraits<T>::valid == true, "T is not valid RPC parameter type.");

  // Write the vector size, followed by  each element
  template <typename S>
  static void write(S& s, const std::vector<T>& v) {
    unsigned len = static_cast<unsigned>(v.size());
    s.write(&len, sizeof(len));
    for (auto&& i : v){
      ParamTraits<T>::write(s, i);
    }
  }

  template <typename S>
  static void read(S& s, std::vector<T>& v) {
    unsigned len;
    s.read(&len, sizeof(len));
    v.clear();
    while (len--) {
      T i;
      ParamTraits<T>::read(s, i);
      v.push_back(std::move(i)); 
    }
  }

  static std::vector<T>&& get(std::vector<T>&& v) { return std::move(v); }
};

struct StringTraits {
  template <typename S>
  static void write(S& s, const char* v) {
    int len = static_cast<int>(strlen(v));
    s.write(&len, sizeof(len));
    s.write(v, len);
  }

  template <typename S>
  static void write(S& s, const std::string& v) {
    int len = static_cast<int>(v.size());
    s.write(&len, sizeof(len));
    s.write(v.c_str(), len);
  }

  template <typename S>
  static void read(S& s, std::string& v) {
    int len;
    s.read(&len, sizeof(len));
    v.clear();

    if (len) {
      v.reserve(len);
      v.append(len, 0);
      s.read(&v[0], len);
    }
  }
};

// Barebones for const char* support
template <>
struct ParamTraits<const char*> {
  static constexpr bool valid = true;
  using store_type = std::string;

  template <typename S>
  static void write(S& s, const char* v) { 
    StringTraits::write(s, v);
  }

  template <typename S>
  static void read(S& s, store_type& v) {
    StringTraits::read(s, v);
  }

  static const char* get(const store_type& v) { return v.c_str(); }
};

template <int N>
struct ParamTraits<char[N]> : ParamTraits<const char*> {};
template <int N>
struct ParamTraits<const char[N]> : ParamTraits<const char*> {};
template <int N>
struct ParamTraits<const char (&)[N]> : ParamTraits<const char*> {};


template <>
struct ParamTraits<std::string> : ParamTraits<const char*> {
  static constexpr bool valid = true;

  template <typename S>
  static void write(S& s, const char* v) { 
    StringTraits::write(s, v);
  }

  template <typename S>
  static void write(S& s, const std::string& v) { 
    StringTraits::write(s, v);
  }

  template <typename S>
  static void read(S& s, std::string& v) {
    StringTraits::read(s, v);
  }

  static const std::string& get(const store_type& v) { return v; }
};

//////////////////////////////////////////////////
// Tuple Traits

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

//////////////////////////////////////////////////
// Function Parameter Traits

template <typename... T>
struct ParamPackTraits {
  static constexpr bool valid = true;
};

template <typename First>
struct ParamPackTraits<First> {
  static constexpr bool valid = ParamTraits<First>::valid;
};

template <typename First, typename... Rest>
struct ParamPackTraits<First, Rest...> {
  static constexpr bool valid = (ParamTraits<First>::valid && ParamPackTraits<Rest...>::valid);
};

//////////////////////////////////////////////////
// Funtion Traits

template <typename F> struct FuncTraits {};

// function
template <typename R, typename... Args>
struct FuncTraits<R(*)(Args...)> : public FuncTraits<R(Args...)> {};

// method pointer
template <typename R, typename C, typename... Args>
struct FuncTraits<R (C::*)(Args...)> : public FuncTraits<R(Args...)> {
  using class_type = C;
};

// const method pointer
template <typename R, typename C, typename... Args>
struct FuncTraits<R (C::*)(Args...) const> : public FuncTraits<R(Args...)> {
  using class_type = C;
};

template <typename R, typename... Args>
struct FuncTraits<R(Args...)> {
  using return_type = R;
  static constexpr bool valid =
      (ParamTraits<return_type>::valid && ParamPackTraits<Args...>::valid);

  using param_tuple = std::tuple<typename ParamTraits<Args>::store_type...>;
  static constexpr std::size_t arity = sizeof...(Args);

  template <std::size_t N>
  struct argument {
    static_assert(N < arity, "error: invalid parameter index.");
    using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
  };
};

// lambda fucntion
template <typename T>
struct FunctionTraits : public FuncTraits<decltype(&T::operator())> {};

//////////////////////////////////////////////////
// serialize

struct ParamPack {
  template <typename S>
  static void serialize(S&) {}

  template <typename S, typename First, typename... Rest>
  static void serialize(S& s, First&& first, Rest&&... rest) {
    using Traits = ParamTraits<First>;
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
    using Traits = ParamTraits<typename FuncTraits<F>::template argument<N>::type>;
    Traits::write(s, std::forward<First>(first));
    Parameters<F, N + 1>::serialize(s, std::forward<Rest>(rest)...);
  }
};

//////////////////////////////////////////////////
// deserialize

template <typename... T>
struct ParamTraits<std::tuple<T...>> {
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

//////////////////////////////////////////////////

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
