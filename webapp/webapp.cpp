#include <iostream>
#include <mutex>
#include <unordered_set>

#include "httplib.h"


using namespace httplib;

class WebServer
{
 public:
  void run()
  {
    Server svr;

    // 🔒 token 存储（模拟登录状态）
    std::unordered_set<std::string> sessions;
    std::mutex mtx;

    // --- 1. 提供静态文件目录 ---
    svr.set_mount_point(
      "/", "E:/abin/projects/httplibDemo/webapp/www");  // 或绝对路径，如 "E:/abin/projects/httplibDemo/webapp/www"

    // --- 2. 登录接口 ---
    svr.Post("/api/login", [&](const Request &req, Response &res) {
      auto user = req.get_param_value("user");
      auto pass = req.get_param_value("pass");

      if (user == "admin" && pass == "123456")
      {
        std::string token = "TOKEN_" + std::to_string(time(nullptr));
        {
          std::lock_guard<std::mutex> lock(mtx);
          sessions.insert(token);
        }
        res.set_content("{\"ok\":true,\"token\":\"" + token + "\"}", "application/json");
      }
      else
      {
        res.set_content("{\"ok\":false,\"msg\":\"Invalid credentials\"}", "application/json");
      }
    });

    // --- 3. 管理接口（需登录） ---
    svr.Get("/api/data", [&](const Request &req, Response &res) {
      auto token = req.get_header_value("Authorization");
      if (token.empty())
      {
        res.status = 401;
        res.set_content("{\"error\":\"no token\"}", "application/json");
        return;
      }

      std::lock_guard<std::mutex> lock(mtx);
      if (sessions.find(token) == sessions.end())
      {
        res.status = 403;
        res.set_content("{\"error\":\"invalid token\"}", "application/json");
        return;
      }

      res.set_content(R"({"data":"Sensitive admin data"})", "application/json");
    });

    // --- 4. 启动服务 ---
    std::cout << "✅ Server started at http://127.0.0.1:8848\n";
    svr.listen("0.0.0.0", 8848);
  }
};

int main()
{
  WebServer().run();
  return 0;
}
