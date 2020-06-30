/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#include <iostream>
#include <string>

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

  return 0;
}
