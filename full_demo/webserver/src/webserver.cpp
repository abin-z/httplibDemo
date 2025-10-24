#include "webserver/webserver.h"

#include <fmt/core.h>

#include <ctime>
#include <filesystem>
#include <vector>

#include "controller/config_controller.h"
#include "controller/data_controller.h"
#include "controller/device_controller.h"
#include "controller/media_controller.h"
#include "controller/operation_controller.h"
#include "controller/temp_controller.h"
#include "fmt/base.h"

WebServer::WebServer(const std::string& ip, int port) : ip_(ip), port_(port) {}

WebServer::~WebServer() = default;

std::string WebServer::extract_token_from_cookie(const std::string& cookie)
{
  size_t pos = cookie.find("token=");
  if (pos == std::string::npos) return {};

  size_t end = cookie.find(';', pos);
  return cookie.substr(pos + 6, end - pos - 6);
}

void WebServer::run()
{
    // --- 1. 提供静态文件目录 ---
    svr_.set_mount_point("/", "E:/projects/httplibDemo/full_demo/www");

  // --- 2. 登录接口 ---
  svr_.Post("/api/login", [&](const httplib::Request& req, httplib::Response& res) {
    auto user = req.get_param_value("user");
    auto pass = req.get_param_value("pass");

    if (user == "admin" && pass == "123456")
    {
      std::string token = "TOKEN_" + std::to_string(time(nullptr));
      {
        std::lock_guard<std::mutex> lock(mtx_);
        sessions_.insert(token);
      }
      res.set_header("Set-Cookie", "token=" + token + "; Path=/; HttpOnly");
      res.set_redirect("/admin.html");
    }
    else
    {
      res.set_content("{\"ok\":false,\"msg\":\"Invalid credentials\"}", "application/json");
    }
  });

  // --- 3. 管理接口（需登录） ---
  svr_.Get("/api/data", [&](const httplib::Request& req, httplib::Response& res) {
    auto token = extract_token_from_cookie(req.get_header_value("Cookie"));

    std::lock_guard<std::mutex> lock(mtx_);
    if (sessions_.find(token) == sessions_.end())
    {
      res.status = 401;
      res.set_content("{\"error\":\"Unauthorized\"}", "application/json");
      return;
    }

    res.set_content(R"({"data":"Sensitive admin data"})", "application/json");
  });

  // --- 4. 拦截 admin.html ---
  svr_.set_pre_routing_handler([&](const httplib::Request& req, httplib::Response& res) {
    if (req.path == "/admin.html")
    {
      auto token = extract_token_from_cookie(req.get_header_value("Cookie"));
      std::lock_guard<std::mutex> lock(mtx_);
      if (sessions_.find(token) == sessions_.end())
      {
        res.set_redirect("/login.html");
        return httplib::Server::HandlerResponse::Handled;
      }
    }
    return httplib::Server::HandlerResponse::Unhandled;
  });

  // 控制器集合
  std::vector<std::unique_ptr<BaseController>> controllers;
  // 注册各个控制器
  controllers.emplace_back(new TempController(svr_));
  controllers.emplace_back(new ConfigController(svr_));
  controllers.emplace_back(new DataController(svr_));
  controllers.emplace_back(new DeviceController(svr_));
  controllers.emplace_back(new MediaController(svr_));
  controllers.emplace_back(new OperationController(svr_));

  for (const auto& ctl : controllers)
  {
    ctl->register_routes();  // 注册路由
  }

  // --- 5. 启动服务 ---
  fmt::print("Web Server started at http://{}:{}\n", ip_, port_);
  svr_.listen(ip_, port_);  // 阻塞
  fmt::print("Web Server stopped.\n");
}

void WebServer::stop()
{
  svr_.stop();
}
