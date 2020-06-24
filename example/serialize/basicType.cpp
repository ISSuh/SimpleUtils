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

  uint32_t serializeUINT32_Arr[5] = {300, 301, 302, 303, 304};
  uint32_t deserializeUINT32_Arr[5] = {0, 0, 0, 0, 0};

  // std::string serializeUINT32_Arr = "asdag";
  // std::string deserializeUINT32_Arr = " ";

  serializer.serialize(serializeUINT32_Arr);
  serializer.deserialize(deserializeUINT32_Arr);

  std::cout << "----------------------------\n";

  for (auto i = 0 ; i < 5 ; ++i) {
    std::cout << "[" << i << "] : " << serializeUINT32_Arr[i] << " / " << deserializeUINT32_Arr[i] << std::endl;
  }

  return 0;
}
