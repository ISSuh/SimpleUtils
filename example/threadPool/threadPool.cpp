/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>
#include <functional>
#include <utility>

#include <sUtils/threadPool/ThreadPool.hpp>

class Test {
 public:
  Test() = delete;

  std::string test(int a, const std::string& s) {
    return std::to_string(a) + " -> " + s;
  }
};

int sum(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
double mul(double a, double b) { return a * b; }

int main() {
  sUtils::ThreadPool threadPool(3);

  std::cout << threadPool.pushTask(&sum, 1, 8).get() << std::endl;
  std::cout << threadPool.pushTask(&sub, 8, 6).get() << std::endl;
  std::cout << threadPool.pushTask(&mul, 8, 6).get() << std::endl;
  std::cout << threadPool.pushTask(&sum, 6, 25).get() << std::endl;
  std::cout << threadPool.pushTask(&sub, 94, 10).get() << std::endl;
  std::cout << threadPool.pushTask(&mul, 8, 2).get() << std::endl;

  Test t;
  // auto func = std::bind(&Test::test, &t, std::placeholders::_1, std::placeholders::_2);
  std::cout << threadPool.pushTask(&t, &Test::test, 1, "asidna").get() << std::endl;

  using returnType = std::decltype(std::declval<Test>(int, const std::string&).test());

  return 0;
}
