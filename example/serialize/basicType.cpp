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
  const std::string s2 = "const string";
  std::string s3 = "string";

  uint32_t d1 = 0;
  std::string d2;
  std::string d3;

  serializer << s1 << s2 << s3;
  serializer >> d1 >> d2 >> d3;

  std::cout << s1 << " / " << d1 << std::endl;
  std::cout << s2 << " / " << d2 << std::endl;
  std::cout << s3 << " / " << d3 << std::endl;

  return 0;
}
