/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>

#include <sUtils.hpp>

int main() {
  uint8_t a = 1;
  uint16_t b = 1;
  uint32_t c = 1;
  uint64_t d = 1;

  sUtils::Serializer serializer;

  serializer.serialize(a);

  a = 0;

  serializer.deserialize(a);

  std::cout << a << std::endl;

  return 0;
}
