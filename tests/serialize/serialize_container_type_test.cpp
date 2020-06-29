/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <vector>

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

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
