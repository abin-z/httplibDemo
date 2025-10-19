#include <iostream>
#include <sstream>

#include "httplib.h"

int main()
{
  httplib::Server svr;

  // 简单日志（可禁用以节省资源）
  svr.set_logger([](const httplib::Request& req, const httplib::Response& res) {
    std::cout << req.method << " " << req.path << " -> " << res.status << std::endl;
  });

  // ------------------------------------------------------------
  // 1️⃣ 基础 GET 示例
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl http://localhost:8080/
  //
  // 📤 响应：
  // Hello, cpp-httplib webserver!
  svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
    res.set_content("Hello, cpp-httplib webserver!", "text/plain");
  });

  // ------------------------------------------------------------
  // 2️⃣ GET 带参数 (/add?a=10&b=20)
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl "http://localhost:8080/add?a=10&b=20"
  //
  // 📤 响应：
  // 30
  //
  // 📦 错误示例：
  // curl "http://localhost:8080/add?a=5"
  //
  // 📤 响应：
  // Missing parameters: a and b are required
  svr.Get("/add", [](const httplib::Request& req, httplib::Response& res) {
    if (!req.has_param("a") || !req.has_param("b"))
    {
      res.status = 400;
      res.set_content("Missing parameters: a and b are required", "text/plain");
      return;
    }
    int a = std::stoi(req.get_param_value("a"));
    int b = std::stoi(req.get_param_value("b"));
    res.set_content(std::to_string(a + b), "text/plain");
  });

  // ------------------------------------------------------------
  // 3️⃣ GET 动态路径参数 (/user/abin)
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl http://localhost:8080/user/abin
  //
  // 📤 响应：
  // Hello, abin!
  svr.Get(R"(/user/(\w+))", [](const httplib::Request& req, httplib::Response& res) {
    std::string username = req.matches[1];
    res.set_content("Hello, " + username + "!", "text/plain");
  });

  // ------------------------------------------------------------
  // 4️⃣ POST 原始数据 (Body Echo)
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl -Method POST -Body "hello cpp" http://localhost:8080/echo
  //
  // 📤 响应：
  // You said: hello cpp
  svr.Post("/echo", [](const httplib::Request& req, httplib::Response& res) {
    if (req.body.empty())
    {
      res.status = 400;
      res.set_content("Empty body received", "text/plain");
    }
    else
    {
      res.set_content("You said: " + req.body, "text/plain");
    }
  });

  // ------------------------------------------------------------
  // 5️⃣ POST JSON (无外部库)
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl -Method POST -ContentType "application/json" -Body '{"name":"abin","age":25}' http://localhost:8080/json
  //
  // 📤 响应：
  // Received JSON (27 bytes):
  // {"name":"abin","age":25}
  svr.Post("/json", [](const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "Received JSON (" << req.body.size() << " bytes):\n" << req.body;
    res.set_content(oss.str(), "text/plain");
  });

  // ------------------------------------------------------------
  // 6️⃣ GET 返回 JSON 内容 (/status)
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl http://localhost:8080/status
  //
  // 📤 响应 (application/json)：
  // {
  //   "status": "ok",
  //   "uptime": 12345,
  //   "version": "1.0.0"
  // }
  svr.Get("/status", [](const httplib::Request&, httplib::Response& res) {
    std::string json =
      R"(
{
  "status": "ok",
  "uptime": 12345,
  "version": "1.0.0"
}
      )";
    res.set_content(json, "application/json");
  });

  // ------------------------------------------------------------
  // 7️⃣ POST 表单数据 (application/x-www-form-urlencoded)
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl -Method POST -Body "user=abin&level=admin" http://localhost:8080/form
  //
  // 📤 响应：
  // Form Data Received:
  // user = abin
  // level = admin
  svr.Post("/form", [](const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "Form Data Received:\n";
    for (const auto& kv : req.params)
    {
      oss << kv.first << " = " << kv.second << "\n";
    }
    res.set_content(oss.str(), "text/plain");
  });

  // ------------------------------------------------------------
  // 8️⃣ 自定义 404 页面
  // ------------------------------------------------------------
  // 📦 PowerShell 请求示例：
  // curl http://localhost:8080/not_exist
  //
  // 📤 响应：
  // Oops! Path /not_exist not found.
  svr.set_error_handler([](const httplib::Request& req, httplib::Response& res) {
    std::string msg = "Oops! Path " + req.path + " not found.\n";
    res.set_content(msg, "text/plain");
    res.status = 404;
  });

  // ------------------------------------------------------------
  // 启动服务
  // ------------------------------------------------------------
  std::cout << "Server running at http://0.0.0.0:8080\n";
  svr.listen("0.0.0.0", 8080);
}
