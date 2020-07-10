/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <vector>
#include <array>

#include <sUtils/serialize/Serializer.hpp>
#include <gtest/gtest.h>

TEST(Serialize, UINT_VECTOR) {
  sUtils::Serializer serializer;

  std::vector<uint32_t> s = {1, 2, 3, 4, 5};
  std::vector<uint32_t> d;

  serializer << s;
  serializer >> d;

  for (size_t i = 0 ; i < s.size() ; ++i) {
    ASSERT_EQ(s[i], d[i]);
  }
}

TEST(Serialize, DOUBLE_VECTOR) {
  sUtils::Serializer serializer;

  std::vector<double> s = {1.1, 2.2, 3.3, 4.4, 5.5};
  std::vector<double> d;

  serializer << s;
  serializer >> d;

  for (size_t i = 0 ; i < s.size() ; ++i) {
    ASSERT_EQ(s[i], d[i]);
  }
}

TEST(Serialize, STRING_VECTOR) {
  sUtils::Serializer serializer;

  std::vector<std::string> s = {"Aa", "Bdasdasd", "Ccccsa", "Degtr", "E12134"};
  std::vector<std::string> d;

  serializer << s;
  serializer >> d;

  for (size_t i = 0 ; i < s.size() ; ++i) {
    ASSERT_EQ(s[i], d[i]);
  }
}

TEST(Serialize, UINT_ARRAY) {
  sUtils::Serializer serializer;

  std::array<uint32_t, 5> s = {1, 2, 3, 4, 5};
  std::array<uint32_t, 5> d;

  serializer << s;
  serializer >> d;

  for (size_t i = 0 ; i < s.size() ; ++i) {
    ASSERT_EQ(s[i], d[i]);
  }
}

TEST(Serialize, DOUBLE_ARRAY) {
  sUtils::Serializer serializer;

  std::array<double, 5> s = {1.1, 2.2, 3.3, 4.4, 5.5};
  std::array<double, 5> d;

  serializer << s;
  serializer >> d;

  for (size_t i = 0 ; i < s.size() ; ++i) {
    ASSERT_EQ(s[i], d[i]);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
