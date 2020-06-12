/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_FUNCMAP_FUNCTIONMAP_HPP_
#define SUTILS_FUNCMAP_FUNCTIONMAP_HPP_

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <utility>
#include <tuple>

#include "Helper.hpp"

namespace sUtils {

// class Action {
//  public:
//     template <typename F>
//     explicit Action(F&& func) : f(std::forward<F>(func)) {}

//     template <typename... Args, int... Is>
//     void func(std::tuple<Args...>& tup, helper::index<Is...>) {
//         f(std::get<Is>(tup)...);
//     }

//     template <typename... Args>
//     void func(const std::tuple<Args...>& tup) {
//         func(tup, helper::gen_seq<sizeof...(Args)>{});
//     }

//     template<typename... Args>
//     void act(Args&&... args) {
//         std::tuple<Args...> params(std::forward<Args>(args)...);

//         func(params);
//     }
// };

// template <typename F>
// Action make_action(F&& f) {
//     return Action (std::forward<F>(f));
// }

// class FunctionMapper {
//  public:
//   FunctionMapper() = default;
//   ~FunctionMapper() = default;

//   template<typename F, typename ...Args>
//   void bindFunction(const std::string& name, F&& f) {
//     registFunction(name, std::forward<F>(f));
//   }

//   template<typename ...Args>
//   void call(const std::string& name, Args&& ...args) {
//     m_functionMap[name](std::forward<Args...>(args...));
//   }

//  private:
//   template<typename F, typename ...Args>
//   void registFunction(const std::string& name, F&& f) {
//     m_functionMap[name] = std::forward<F>(f);
//   }

//  private:
//   std::map<std::string, std::function<void()>> m_functionMap;
// };

// Check if a function signature "R(A)" only uses arithmetic types

}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_FUNCTIONMAP_HPP_
