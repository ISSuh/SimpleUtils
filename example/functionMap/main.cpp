/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>

#include <sUtils.hpp>

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
  sUtils::FunctionMapper fM;
  fM.bindFunction("HelloWorld", HelloWorld);
  fM.bindFunction("printArg", printArg);
  fM.bindFunction("sum", sum);

  fM.call("HelloWorld");
  fM.call("printArg", "TEST");
  fM.call("sum", 1, 1);

  return 0;
}
