/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <string>

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

  int8_t serializeINT8 = -8;
  int16_t serializeINT16 = -16;
  int32_t serializeINT32 = -32;
  int64_t serializeINT64 = -64;

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

TEST(Serialize, INT_ARRAY) {
  sUtils::Serializer serializer;

  int32_t serializeINT32_Arr[5] = {-1, -2, -3, -4, -5};
  int32_t deserializeINT32_Arr[5] = {0, 0, 0, 0, 0};

  serializer.serialize(serializeINT32_Arr);
  serializer.deserialize(deserializeINT32_Arr);

  for (auto i = 0 ; i < 5 ; ++i) {
    ASSERT_EQ(serializeINT32_Arr[i], deserializeINT32_Arr[i]);
  }
}

TEST(Serialize, FLOAT) {
  sUtils::Serializer serializer;

  float serializeFLOAT = 4.4;
  double serializeDOUBLE = 8.8;
  float dstFloat = 0;
  double dstDouble = 0;

  serializer.serialize(serializeFLOAT);
  serializer.serialize(serializeDOUBLE);

  serializer.deserialize(dstFloat);
  serializer.deserialize(dstDouble);

  ASSERT_EQ(serializeFLOAT, dstFloat);
  ASSERT_EQ(serializeDOUBLE, dstDouble);
}


TEST(Serialize, FLOAT_ARRAY) {
  sUtils::Serializer serializer;

  float serializeFLOAT_Arr[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  float dst[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

  serializer.serialize(serializeFLOAT_Arr);
  serializer.deserialize(dst);

  for (auto i = 0 ; i < 5 ; ++i) {
    ASSERT_EQ(serializeFLOAT_Arr[i], dst[i]);
  }
}

TEST(Serialize, CONST_CHAR_PTR) {
  sUtils::Serializer serializer;

  const char* cStr = "const char*";
  const char* dst = "";

  serializer.serialize(cStr);
  serializer.deserialize(dst);

  ASSERT_EQ(cStr, dst);
}

TEST(Serialize, STRING) {
  sUtils::Serializer serializer;

  std::string str("std::string");
  std::string dst("");

  serializer.serialize(str);
  serializer.deserialize(dst);

  ASSERT_EQ(str, dst);
}

TEST(Serialize, CONST_STRING_REFERENCE) {
  sUtils::Serializer serializer;

  const std::string& str = "std::string";
  std::string dst("");

  serializer.serialize(str);
  serializer.deserialize(dst);

  ASSERT_EQ(str, dst);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
