/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>
#include <string>

#include <vector>
#include <array>
#include <map>

#include <sUtils/serialize/Serializer.hpp>

int main() {
  std::cout << "=========================================\n";
  std::cout << "Serialize Example - Container Type\n";
  std::cout << "=========================================\n";

  sUtils::Serializer serializer;

  std::vector<std::string> s = {"Aaasdasdasdasdadaasdasaasads", "Bdasdasd", "Ccccsa", "Degtr", "E12134"};
  std::vector<std::string> d;

  serializer << s;
  serializer >> d;

  for (size_t i = 0 ; i < s.size() ; ++i) {
    std::cout << "vector : [" << i << "] : " <<  s[i] << " / " << d[i] << std::endl;
  }

  std::cout << "=========================================\n";

  std::array<uint32_t, 5> arrayS = {1, 2, 3, 4, 5};
  std::array<uint32_t, 5> arrayD;

  serializer << arrayS;
  serializer >> arrayD;

  for (size_t i = 0 ; i < s.size() ; ++i) {
    std::cout << "array : [" << i << "] : " <<  arrayS[i] << " / " << arrayD[i] << std::endl;
  }

  // sUtils::type::helper::ArrayTraits<decltype(arrayS)>::type

  std::cout << "=========================================\n";

  std::map<uint32_t, uint32_t> mapS = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<uint32_t, uint32_t> mapD;

  serializer << mapS;
  serializer >> mapD;

  for (size_t i = 1 ; i <= 5 ; ++i) {
    std::cout << "map : [" << i << "] : " <<  mapS[i] << " / " << mapD[i] << std::endl;
  }

  return 0;
}
