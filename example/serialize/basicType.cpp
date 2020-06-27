/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>
#include <string>

#include <sUtils/serialize/Serializer.hpp>

int main() {
  std::cout << "Serialize Example\n\n";

  sUtils::Serializer serializer;

  uint32_t uint32Arr[5] = {300, 301, 302, 303, 304};
  uint32_t dst_uint32Arr[5] = {0, 0, 0, 0, 0};
  float float32Arr[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
  float dst_float32Arr[5] = {0, 0, 0, 0, 0};

  serializer.serialize(uint32Arr);
  serializer.serialize(float32Arr);

  serializer.deserialize(dst_uint32Arr);
  serializer.deserialize(dst_float32Arr);

  for (auto i = 0 ; i < 5 ; ++i) {
    std::cout << "***********************************\n";
    std::cout << "uint32_t : [" << i << "] : " << uint32Arr[i] << " / " << dst_uint32Arr[i] << std::endl;
    std::cout << "float : [" << i << "] : " << float32Arr[i] << " / " << dst_float32Arr[i] << std::endl;
  }

  std::cout << "=========================================\n";
  std::string constChar("CONST STRING REFERENCE");
  std::string de_constChar = "";

  serializer.serialize(constChar);
  serializer.deserialize(de_constChar);

  std::cout << constChar << " / " << de_constChar << std::endl;

  // sUtils::type::helper::is_string<std::string>::value;

  return 0;
}
