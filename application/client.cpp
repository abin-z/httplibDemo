/*
 * client.cpp 演示了如何使用 cpp-httplib 创建一个简单的 HTTP 客户端，
 */

#include <iostream>

#include "httplib.h"

int main()
{
  // ------------------------------------------------------------
  // 创建客户端 (连接到本地 8080 端口)
  // ------------------------------------------------------------
  httplib::Client cli("http://localhost:8080");
  // cli.set_keep_alive(true); // 保持连接

  // ------------------------------------------------------------
  // 1️⃣ 基础 GET 请求
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl http://localhost:8080/
  //
  // 📤 响应：
  // Hello, cpp-httplib webserver!
  if (auto res = cli.Get("/"))
  {
    std::cout << "[GET /] " << res->status << "\n" << res->body << "\n\n";
  }
  else
  {
    std::cerr << "Request failed\n";
  }

  // ------------------------------------------------------------
  // 2️⃣ GET 带参数 (/add?a=10&b=20)
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl "http://localhost:8080/add?a=10&b=20"
  if (auto res = cli.Get("/add?a=10&b=20"))
  {
    std::cout << "[GET /add] " << res->status << "\nResult = " << res->body << "\n\n";
  }

  // ------------------------------------------------------------
  // 3️⃣ GET 动态路径参数 (/user/abin)
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl http://localhost:8080/user/abin
  if (auto res = cli.Get("/user/abin"))
  {
    std::cout << "[GET /user/abin] " << res->status << "\n" << res->body << "\n\n";
  }

  // ------------------------------------------------------------
  // 4️⃣ POST 原始数据 (Body)
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl -Method POST -Body "hello cpp" http://localhost:8080/echo
  if (auto res = cli.Post("/echo", "hello cpp", "text/plain"))
  {
    std::cout << "[POST /echo] " << res->status << "\n" << res->body << "\n\n";
  }

  // ------------------------------------------------------------
  // 5️⃣ POST JSON
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl -Method POST -ContentType "application/json" -Body '{"name":"abin","age":25}' http://localhost:8080/json
  std::string json_body = R"({"name":"abin","age":25})";
  if (auto res = cli.Post("/json", json_body, "application/json"))
  {
    std::cout << "[POST /json] " << res->status << "\n" << res->body << "\n\n";
  }

  // ------------------------------------------------------------
  // 6️⃣ GET JSON 响应 (/status)
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl http://localhost:8080/status
  if (auto res = cli.Get("/status"))
  {
    std::cout << "[GET /status] " << res->status << "\n" << res->body << "\n\n";
  }

  // ------------------------------------------------------------
  // 7️⃣ POST 表单数据 (application/x-www-form-urlencoded)
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl -Method POST -Body "user=abin&level=admin" http://localhost:8080/form
  httplib::Params params;
  params.emplace("user", "abin");
  params.emplace("level", "admin");

  if (auto res = cli.Post("/form", params))
  {
    std::cout << "[POST /form] " << res->status << "\n" << res->body << "\n\n";
  }

  // ------------------------------------------------------------
  // 8️⃣ 自定义 Header 请求
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl -H "X-Token: 12345" http://localhost:8080/status
  httplib::Headers headers = {{"X-Token", "12345"}, {"User-Agent", "cpp-httplib-client/1.0"}};
  if (auto res = cli.Get("/status", headers))
  {
    std::cout << "[GET /status + headers] " << res->status << "\n" << res->body << "\n\n";
  }

  // ------------------------------------------------------------
  // 9️⃣ 处理 404 错误
  // ------------------------------------------------------------
  // 📦 PowerShell 等价请求：
  // curl http://localhost:8080/not_exist
  if (auto res = cli.Get("/not_exist"))
  {
    std::cout << "[GET /not_exist] " << res->status << "\n" << res->body << "\n\n";
  }

  std::cout << "All client requests done.\n";
}
