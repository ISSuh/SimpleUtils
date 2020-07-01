/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>
#include <string>

#include <sUtils/serialize/Serializer.hpp>

int main() {
  std::cout << "Serialize Example\n";

  sUtils::Serializer serializer;

  uint32_t s1 = 300;
  float s2 = 1.1;

  uint32_t d1 = 0;
  float d2 = 0;

  serializer << s1 << s2;
  serializer >> d1 >> d2;

  std::cout << s1 << " / " << d1 << std::endl;
  std::cout << s2 << " / " << d2 << std::endl;

  return 0;
}
