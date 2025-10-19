#include "httplib.h"
#include <iostream>

int main() {
  httplib::Server svr;

  // 处理 GET 请求
  svr.Get("/hello", [](const httplib::Request&, httplib::Response& res) {
    res.set_content("Hello, cpp-httplib!", "text/plain");
  });

  // 处理 POST 请求
  svr.Post("/echo", [](const httplib::Request& req, httplib::Response& res) {
    res.set_content(req.body, "text/plain");
  });

  std::cout << "Server started at http://0.0.0.0:8080\n";
  svr.listen("0.0.0.0", 8080);
}
