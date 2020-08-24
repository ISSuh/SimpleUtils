/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_FUNCMAP_FUNCTIONMAP_HPP_
#define SUTILS_FUNCMAP_FUNCTIONMAP_HPP_

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <thread>
#include <functional>
#include <utility>
#include <memory>
#include <future>
#include <condition_variable>

namespace sUtils {

struct return_void {};
struct return_non_void{};

template<typename R> struct FunctReturnTrait {
  using type = return_non_void;
};

template<> struct FunctReturnTrait<void> {
  using type = return_void;
};

template <typename F> struct FuncTraits {};

// function
template <typename R, typename... Args>
struct FuncTraits<R(Args...)> {
  using return_type = R;
  using return_type_info = typename FunctReturnTrait<return_type>::type;
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

class Function {
 public:
  Function() = default;
  ~Function() = default;

  template<class F>
  void regist(F&& func) {
    using returnType = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<returnType()>>(
                  std::bind(std::forward<F>(func), std::forward<Args>(args)...));

    m_funcWrapper = [task](){ (*task)(); };
  }

 private:
  std::string m_functionName;
  std::function<void()> m_funcWrapper;
};

// class FunctionMapper {
//  public:
//   FunctionMapper() = default;
//   ~FunctionMapper() = default;

//   template<class F, class ...Args>
//   void regiset(const std::string& name, F&& func, Args&&... args) {
//     using returnType = typename std::result_of<F(Args...)>::type;

//     auto task = std::make_shared<std::packaged_task<returnType()>>(
//                   std::bind(std::forward<F>(func), std::forward<Args>(args)...));
//     std::future<returnType> taskReturn = task->get_future();

//     m_map.insert({name, [task](){ (*task)(); });
//   }

//   void unRegist() {

//   }

//   template<class R>
//   R call(const std::string& name) {
//     return m_map[name];
//   }

//   bool has() {

//   }

//  private:

//  private:
//   std::map<std::string, std::function<void()>> m_map;
// };

}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_FUNCTIONMAP_HPP_
