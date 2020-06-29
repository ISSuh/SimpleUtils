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

  serializer << serializeUINT8 << serializeUINT16 << serializeUINT32 << serializeUINT64;
  serializer >> deserializeUINT8 >> deserializeUINT16 >> deserializeUINT32 >> deserializeUINT64;

  ASSERT_EQ(serializeUINT8, deserializeUINT8);
  ASSERT_EQ(serializeUINT16, deserializeUINT16);
  ASSERT_EQ(serializeUINT32, deserializeUINT32);
  ASSERT_EQ(serializeUINT64, deserializeUINT64);
}

TEST(Serialize, UINT_ARRAY) {
  sUtils::Serializer serializer;

  uint32_t serializeUINT32_Arr[5] = {1, 2, 3, 4, 5};
  uint32_t deserializeUINT32_Arr[5] = {0, 0, 0, 0, 0};

  serializer << serializeUINT32_Arr;
  serializer >> deserializeUINT32_Arr;

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

  serializer << serializeINT8 << serializeINT16 << serializeINT32 << serializeINT64;
  serializer >> deserializeINT8 >> deserializeINT16 >> deserializeINT32 >> deserializeINT64;

  ASSERT_EQ(serializeINT8, deserializeINT8);
  ASSERT_EQ(serializeINT16, deserializeINT16);
  ASSERT_EQ(serializeINT32, deserializeINT32);
  ASSERT_EQ(serializeINT64, deserializeINT64);
}

TEST(Serialize, INT_ARRAY) {
  sUtils::Serializer serializer;

  int32_t serializeINT32_Arr[5] = {-1, -2, -3, -4, -5};
  int32_t deserializeINT32_Arr[5] = {0, 0, 0, 0, 0};

  serializer << serializeINT32_Arr;
  serializer >> deserializeINT32_Arr;

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

  serializer << serializeFLOAT << serializeDOUBLE;
  serializer >> dstFloat >> dstDouble;

  ASSERT_EQ(serializeFLOAT, dstFloat);
  ASSERT_EQ(serializeDOUBLE, dstDouble);
}


TEST(Serialize, FLOAT_ARRAY) {
  sUtils::Serializer serializer;

  float serializeFLOAT_Arr[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  float dst[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

  serializer << serializeFLOAT_Arr;
  serializer >> dst;

  for (auto i = 0 ; i < 5 ; ++i) {
    ASSERT_EQ(serializeFLOAT_Arr[i], dst[i]);
  }
}

TEST(Serialize, STRING) {
  sUtils::Serializer serializer;

  std::string str("std::string");
  std::string dst("");

  serializer << str;
  serializer >> dst;

  ASSERT_EQ(str, dst);
}

TEST(Serialize, CONST_STRING_REFERENCE) {
  sUtils::Serializer serializer;

  const std::string& str = "std::string";
  std::string dst("");

  serializer << str;
  serializer >> dst;

  ASSERT_EQ(str, dst);
}

TEST(Serialize, MIX) {
  const size_t LEN = 3;

  sUtils::Serializer serializer;

  int32_t s1 = -32;
  uint8_t s2 = 8;
  double s3 = 8.8;
  int32_t s4 = -32;
  const std::string& s6("const std::string&");
  uint16_t s7[LEN] = {5, 6, 7};
  float s8[LEN] = {5.5, 6.6, 7.7};

  int32_t d1;
  uint8_t d2;
  double d3;
  int32_t d4;
  std::string d6("");
  uint16_t d7[LEN];
  float d8[LEN];

  serializer << s1 << s2 << s3 << s4 << s6 << s7 << s8;

  serializer >> d1 >> d2 >> d3 >> d4 >> d6 >> d7 >> d8;

  ASSERT_EQ(s1, d1);
  ASSERT_EQ(s2, d2);
  ASSERT_EQ(s3, d3);
  ASSERT_EQ(s4, d4);
  ASSERT_EQ(s6, d6);

  for (size_t i = 0 ; i < LEN ; ++i) {
    ASSERT_EQ(s7[i], d7[i]);
    ASSERT_EQ(s8[i], d8[i]);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
