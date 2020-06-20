/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>

#include <sUtils/serialize/Serializer.hpp>

int main() {
  uint32_t a = 10;
  uint32_t b = 20;
  uint32_t aa;
  uint32_t bb;

  std::cout << "Before\n";
  std::cout << "A : " << std::showbase << std::hex << a << std::endl;
  std::cout << "B : " << std::showbase << std::hex << b << std::endl;

  sUtils::Serializer serializer;
  serializer.serialize(a);
  serializer.serialize(b);

  serializer.deserialize(aa);
  serializer.deserialize(bb);

  std::cout << "Deserialize\n";
  std::cout << "A : " << std::showbase << std::hex << aa << std::endl;
  std::cout << "B : " << std::showbase << std::hex << bb << std::endl;

  return 0;
}
