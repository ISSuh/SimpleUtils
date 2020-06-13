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
#include "Stream.hpp"

namespace sUtils {

class FunctionMapper {
 public:
  FunctionMapper() = default;
  ~FunctionMapper() = default;

  template<typename F, typename ...Args>
  void bindFunction(const std::string& name, F&& f) {
    registFunction(name, std::forward<F>(f));
  }

  template<typename Arg, typename ...Args>
  void call(const std::string& name, stream::Stream& serial, Arg&& arg) {
    helper::ParamPack::serialize(serial, arg);

    m_functionMap[name](serial);
  }

  template<typename Arg, typename ...Args>
  void call(const std::string& name, stream::Stream& serial, Arg&& arg, Args&& ...args) {
    helper::ParamPack::serialize(serial, arg);

    call(name, serial, args...);
  }

  template<typename Arg, typename ...Args>
  void call(const std::string& name, Arg&& arg, Args&& ...args) {
    stream::Stream serial;
    helper::ParamPack::serialize(serial, arg);

    call(name, serial, args...);
  }

 private:
  template<typename F>
  struct Invoker {
    static void noMember(F f, stream::Stream s) {
      using traits = helper::FuncTraits<decltype(f)>;
      static_assert(traits::valid, "Invalid");
      typename traits::param_tuple parmasTuple;
      helper::ParamTraits<decltype(parmasTuple)>::read(s, parmasTuple);

      helper::callMethod(f, std::move(parmasTuple));
    }
  };

 private:
  template<typename F>
  void registFunction(const std::string& name, F f) {
    m_functionMap[name] = {
      std::bind(&Invoker<F>::noMember, f, std::placeholders::_1)
    };
  }

 private:
  std::map<std::string, std::function<void(stream::Stream)>> m_functionMap;
};

}  // namespace sUtils

#endif  // SUTILS_FUNCMAP_FUNCTIONMAP_HPP_
