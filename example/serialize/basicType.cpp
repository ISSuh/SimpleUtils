/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>

#include <sUtils/serialize/Serializer.hpp>

int main() {
  uint8_t serializeUINT8 = 8;
  uint16_t serializeUINT16 = 16;
  uint32_t serializeUINT32 = 32;
  uint64_t serializeUINT64 = 64;

  uint8_t deserializeUINT8 = 0;
  uint16_t deserializeUINT16 = 0;
  uint32_t deserializeUINT32 = 0;
  uint64_t deserializeUINT64 = 0;

  sUtils::Serializer serializer;
  serializer.serialize(serializeUINT8);
  serializer.serialize(serializeUINT16);
  serializer.serialize(serializeUINT32);
  serializer.serialize(serializeUINT64);

  serializer.deserialize(deserializeUINT8);
  serializer.deserialize(deserializeUINT16);
  serializer.deserialize(deserializeUINT32);
  serializer.deserialize(deserializeUINT64);

  return 0;
}
