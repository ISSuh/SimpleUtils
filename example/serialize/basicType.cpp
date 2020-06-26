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

  std::cout << "----------------------------\n";

  serializer.serialize(serializeUINT32_Arr);
  serializer.deserialize(deserializeUINT32_Arr);

  for (auto i = 0 ; i < 5 ; ++i) {
    std::cout << "[" << i << "] : " << serializeUINT32_Arr[i] << " / " << deserializeUINT32_Arr[i] << std::endl;
  }

  std::cout << "----------------------------\n";

  float serializeUINT32 = 300;
  float deserializeUINT32 = 0;

  serializer.serialize(serializeUINT32);
  serializer.deserialize(deserializeUINT32);

  std::cout << "[" << 0 << "] : " << serializeUINT32 << " / " << deserializeUINT32 << std::endl;

  uint32_t test[5];
  sUtils::type::helper::UintTraits<float[5]>::type test2;
  sUtils::type::helper::FloatTraits<float>::type test3;

  return 0;
}
