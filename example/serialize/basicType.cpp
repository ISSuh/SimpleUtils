/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>

#include <sUtils/serialize/Serializer.hpp>

int main() {
  uint32_t serializeUINT32 = 32;
  uint32_t deserializeUINT32 = 0;

  sUtils::Serializer serializer;
  serializer.serialize(serializeUINT32);
  serializer.deserialize(deserializeUINT32);

  return 0;
}
