/**
 * 
 *  Copyright:  Copyright (c) 2020, ISSuh
 * 
 */

#ifndef SUTILS_CHNNEL_CHNNEL_HPP_
#define SUTILS_CHNNEL_CHNNEL_HPP_

#include <string>
#include <memory>

#include "session.hpp"

class Channel {
 public:
  Channel() {}
  ~Channel() {}

  void Open();
  void Close();

 private:
  std::unique_ptr<Session> session_;
  const std::string topic_;
};

#endif // SUTILS_CHNNEL_CHNNEL_HPP_
