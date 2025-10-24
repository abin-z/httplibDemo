#pragma once

#include <mutex>
#include <string>
#include <unordered_set>

#include "httplib.h"

class WebServer
{
 public:
  WebServer(const std::string& ip, int port);
  ~WebServer();

  void run();
  void stop();

 private:
  std::string ip_;
  int port_;

  httplib::Server svr_;
  std::unordered_set<std::string> sessions_;
  std::mutex mtx_;

  // 提取 cookie 中的 token
  std::string extract_token_from_cookie(const std::string& cookie);
};
