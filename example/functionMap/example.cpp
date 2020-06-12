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

  //  ERROR
  static_assert(ParamTraits<const std::string&>::valid == true, "");
  static_assert(ParamTraits<const char*>::valid == true, "");

  using Traits = FuncTraits<decltype(&sum)>;
  static_assert(Traits::valid, "");
  Traits::argument<0>::type p0;

  return 0;
}
