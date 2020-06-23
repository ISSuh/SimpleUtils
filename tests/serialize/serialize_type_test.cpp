/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <gtest/gtest.h>

#include <sUtils/serialize/Serializer.hpp>

TEST(Serialize, UINT) {
  sUtils::Serializer serializer;

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

  ASSERT_EQ(serializeUINT8, deserializeUINT8);
  ASSERT_EQ(serializeUINT16, deserializeUINT16);
  ASSERT_EQ(serializeUINT32, deserializeUINT32);
  ASSERT_EQ(serializeUINT64, deserializeUINT64);
}

TEST(Serialize, UINT_ARRAY) {
  sUtils::Serializer serializer;

  uint32_t serializeUINT32_Arr[5] = {1, 2, 3, 4, 5};

  uint32_t deserializeUINT32_Arr[5] = {0, 0, 0, 0, 0};

  serializer.serialize(serializeUINT32_Arr);

  serializer.deserialize(deserializeUINT32_Arr);

  for (auto i = 0 ; i < 5 ; ++i) {
    ASSERT_EQ(serializeUINT32_Arr[i], deserializeUINT32_Arr[i]);
  }
}

TEST(Serialize, INT) {
  sUtils::Serializer serializer;

  int8_t serializeINT8 = 8;
  int16_t serializeINT16 = 16;
  int32_t serializeINT32 = 32;
  int64_t serializeINT64 = 64;

  int8_t deserializeINT8 = 0;
  int16_t deserializeINT16 = 0;
  int32_t deserializeINT32 = 0;
  int64_t deserializeINT64 = 0;

  serializer.serialize(serializeINT8);
  serializer.serialize(serializeINT16);
  serializer.serialize(serializeINT32);
  serializer.serialize(serializeINT64);

  serializer.deserialize(deserializeINT8);
  serializer.deserialize(deserializeINT16);
  serializer.deserialize(deserializeINT32);
  serializer.deserialize(deserializeINT64);

  ASSERT_EQ(serializeINT8, deserializeINT8);
  ASSERT_EQ(serializeINT16, deserializeINT16);
  ASSERT_EQ(serializeINT32, deserializeINT32);
  ASSERT_EQ(serializeINT64, deserializeINT64);
}

TEST(Serialize, FLOAT) {
  sUtils::Serializer serializer;

  float serializeFLOAT = 4.4;
  double serializeDOUBLE = 8.8;
  float deserializeFLOAT = 0;
  double deserializeDOUBLE = 0;

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
