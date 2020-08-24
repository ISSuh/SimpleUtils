/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>

#include <sUtils/funcMap/FunctionMap.hpp>

std::string log(const char* log) { return log; }
int sum(int a, int b) { return a + b; }

int main() {
  sUtils::Function func;

  func.regist(&sum, 1, 2);
  
  // funcMap.regiset("log", &log, "hello world!");
  // funcMap.regiset("sum", &sum, 1, 2);

  // std::cout << funcMap.call("log").get() << std::endl;
  // std::cout << funcMap.call("sum").get() << std::endl;

  return 0;
}
