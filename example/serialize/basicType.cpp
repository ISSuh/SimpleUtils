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

  uint8_t serializeUINT8 = 8;
  uint16_t serializeUINT16 = 16;
  uint32_t serializeUINT32 = 32;
  uint64_t serializeUINT64 = 64;

  uint8_t deserializeUINT8 = 0;
  uint16_t deserializeUINT16 = 0;
  uint32_t deserializeUINT32 = 0;
  uint64_t deserializeUINT64 = 0;

  serializer.serialize(serializeUINT8);
  serializer.serialize(serializeUINT16);
  serializer.serialize(serializeUINT32);
  serializer.serialize(serializeUINT64);

  serializer.deserialize(deserializeUINT8);
  serializer.deserialize(deserializeUINT16);
  serializer.deserialize(deserializeUINT32);
  serializer.deserialize(deserializeUINT64);

  std::cout << serializeUINT8 << " / " << deserializeUINT8 << std::endl;
  std::cout << serializeUINT16 << " / " << deserializeUINT16 << std::endl;
  std::cout << serializeUINT32 << " / " << deserializeUINT32 << std::endl;
  std::cout << serializeUINT64 << " / " << deserializeUINT64 << std::endl;

  std::cout << "=========================================\n";

  std::string s1("string");
  std::string d1("");

  serializer << s1;
  serializer >> d1;

  std::cout << s1 << " / " << d1 << std::endl;

  return 0;
}
