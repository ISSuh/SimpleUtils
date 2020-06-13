/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>

#include <sUtils.hpp>

using namespace sUtils::helper;

void HelloWorld() {
  std::cout << "HelloWorld" << std::endl;
}

void printArg(const std::string& arg) {
  std::cout << arg << std::endl;
}

int sum(int a, int b) {
  return a + b;
}

int main() {
  using TraitsHelloWorld = FuncTraits<decltype(&HelloWorld)>;
  static_assert(TraitsHelloWorld::valid, "Invalid");

  using TraitsPrintArg = FuncTraits<decltype(&printArg)>;
  static_assert(TraitsPrintArg::valid, "Invalid");
  TraitsPrintArg::argument<0>::type p0{};
  TraitsPrintArg::param_tuple params1;

  using TraitsSum = FuncTraits<decltype(&sum)>;
  static_assert(TraitsSum::valid, "Invalid");
  TraitsSum::argument<0>::type p2 = 0;
  TraitsSum::argument<1>::type p3 = 0;
  TraitsSum::param_tuple params2;

  ////////////////

  sUtils::stream::Stream s1;
  Parameters<decltype(&printArg), 0>::serialize(s1, "Hello");
  TypeTraits<decltype(params1)>::read(s1, params1);
  std::cout << std::get<0>(params1) << std::endl;
  callMethod(&printArg, std::move(params1));

  sUtils::stream::Stream s2;
  Parameters<decltype(&sum), 0>::serialize(s2, 1, 2);
  TypeTraits<decltype(params2)>::read(s2, params2);
  std::cout << std::get<0>(params2) << std::endl;
  std::cout << std::get<1>(params2) << std::endl;
  auto res = callMethod(&sum, std::move(params2));
  std::cout << res << std::endl;

  ////////////////

  sUtils::FunctionMapper fM;
  fM.bindFunction("HelloWorld", &HelloWorld);
  // fM.bindFunction("printArg", &printArg);
  fM.bindFunction("sum", &sum);

  fM.call("HelloWorld");
  // fM.call("printArg", "TEST");
  fM.call("sum", 1, 1);

  return 0;
}
