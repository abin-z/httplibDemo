#include <iostream>
#include <mutex>
#include <string>
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
    svr.set_mount_point("/", "E:/abin/projects/httplibDemo/webapp/www");  // 或绝对路径

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
        // 设置 HttpOnly cookie
        res.set_header("Set-Cookie", "token=" + token + "; Path=/; HttpOnly");
        res.set_redirect("/admin.html");  // 登录成功跳转
      }
      else
      {
        res.set_content("{\"ok\":false,\"msg\":\"Invalid credentials\"}", "application/json");
      }
    });

    // --- 3. 管理接口（需登录，校验 cookie） ---
    svr.Get("/api/data", [&](const Request &req, Response &res) {
      auto cookie = req.get_header_value("Cookie");
      std::string token;

      size_t pos = cookie.find("token=");
      if (pos != std::string::npos)
      {
        size_t end = cookie.find(';', pos);
        token = cookie.substr(pos + 6, end - pos - 6);
      }

      std::lock_guard<std::mutex> lock(mtx);
      if (sessions.find(token) == sessions.end())
      {
        res.status = 401;
        res.set_content("{\"error\":\"Unauthorized\"}", "application/json");
        return;
      }

      res.set_content(R"({"data":"Sensitive admin data"})", "application/json");
    });

    // --- 4. 后端拦截 admin.html ---
    // 使用 set_pre_routing_handler 可以在路由匹配前拦截请求
    svr.set_pre_routing_handler([&](const Request &req, Response &res) {
      if (req.path == "/admin.html")
      {
        auto cookie = req.get_header_value("Cookie");
        std::string token;

        size_t pos = cookie.find("token=");
        if (pos != std::string::npos)
        {
          size_t end = cookie.find(';', pos);
          token = cookie.substr(pos + 6, end - pos - 6);
        }

        std::lock_guard<std::mutex> lock(mtx);
        if (sessions.find(token) == sessions.end())
        {
          res.set_redirect("/login.html");
          return Server::HandlerResponse::Handled;
        }
      }
      return Server::HandlerResponse::Unhandled;
    });

    // --- 5. 启动服务 ---
    std::cout << "✅ Server started at http://127.0.0.1:8848\n";
    svr.listen("0.0.0.0", 8848);
  }
};

int main()
{
  WebServer().run();
  return 0;
}
