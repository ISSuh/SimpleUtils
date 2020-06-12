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
  // sUtils::FunctionMapper fM;
  // fM.bindFunction("HelloWorld", &HelloWorld);
  // fM.bindFunction("printArg", &printArg);
  // fM.bindFunction("sum", sum);

  // fM.call("HelloWorld");
  // fM.call("printArg", "TEST");
  // fM.call("sum", 1, 1);

  //  OK
  static_assert(ParamTraits<int>::valid == true, "Invalid");
  static_assert(ParamTraits<const int&>::valid == true, "Invalid");
  static_assert(ParamTraits<const double&>::valid == true, "Invalid");
  static_assert(ParamTraits<double*>::valid == true, "Invalid");
  static_assert(ParamTraits<std::vector<int>>::valid == true, "Invalid");
  static_assert(ParamTraits<const std::string&>::valid == true, "Invalid");
  static_assert(ParamTraits<const char*>::valid == true, "Invalid");

  using TraitsHelloWorld = FuncTraits<decltype(&HelloWorld)>;
  static_assert(TraitsHelloWorld::valid, "Invalid");

  using TraitsPrintArg = FuncTraits<decltype(&printArg)>;
  static_assert(TraitsPrintArg::valid, "Invalid");
  TraitsPrintArg::argument<0>::type p0{};

  using TraitsSum = FuncTraits<decltype(&sum)>;
  static_assert(TraitsSum::valid, "Invalid");
  TraitsSum::argument<0>::type p2 = 0;
  TraitsSum::argument<1>::type p3 = 0;

  return 0;
}
