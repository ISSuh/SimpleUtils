/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <gtest/gtest.h>

#include <sUtils/serialize/Serializer.hpp>

TEST(Serialize, Uint) {
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

  ASSERT_EQ(serializeUINT8, deserializeUINT8);
  ASSERT_EQ(serializeUINT16, deserializeUINT16);
  ASSERT_EQ(serializeUINT32, deserializeUINT32);
  ASSERT_EQ(serializeUINT64, deserializeUINT64);
}

TEST(Serialize, Float) {
  float serializeFLOAT = 4.4;
  double serializeDOUBLE = 8.8;
  float deserializeFLOAT = 0;
  double deserializeDOUBLE = 0;

  sUtils::Serializer serializer;
  serializer.serialize(serializeFLOAT);
  serializer.serialize(serializeDOUBLE);

  serializer.deserialize(deserializeFLOAT);
  serializer.deserialize(deserializeDOUBLE);

  ASSERT_EQ(serializeFLOAT, deserializeFLOAT);
  ASSERT_EQ(serializeDOUBLE, deserializeDOUBLE);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
