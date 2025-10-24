// logintest.cpp 演示了一个简单的登录系统，包含用户认证和 session 管理功能。

#include <unordered_map>

#include "httplib.h"

// ----------------------------
// 用户数据库（模拟）
// ----------------------------
// key   : 用户名
// value : 密码
std::unordered_map<std::string, std::string> user_db = {{"admin", "123456"}, {"guest", "guest"}};

// ----------------------------
// session 存储
// key   : token
// value : 用户名
// ----------------------------
std::unordered_map<std::string, std::string> sessions;

// ----------------------------
// 生成简单 token
// ----------------------------
std::string generate_token()
{
  static int counter = 0;
  return "token" + std::to_string(++counter);  // 简单递增 token
}

// ----------------------------
// 检查 session 是否有效
// ----------------------------
bool check_session(const httplib::Request& req)
{
  auto it = req.headers.find("Cookie");  // 获取 Cookie
  if (it == req.headers.end()) return false;

  std::string cookie = it->second;
  size_t pos = cookie.find("token=");  // 查找 token
  if (pos == std::string::npos) return false;

  std::string token = cookie.substr(pos + 6);
  return sessions.count(token) > 0;  // token 是否存在
}

int main()
{
  httplib::Server svr;

  svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
    res.set_content(R"(hello to the login test! <a href='/login'>Login</a>)", "text/html");
  });

  // ----------------------------
  // 登录页面 (GET /login)
  // ----------------------------
  // 浏览器访问 /login，会返回一个 HTML 表单
  svr.Get("/login", [](const httplib::Request&, httplib::Response& res) {
    res.set_content(R"(
            <form method="POST" action="/login">
                Username: <input name="user"/><br/>
                Password: <input type="password" name="pass"/><br/>
                <input type="submit"/>
            </form>
        )",
                    "text/html");
  });

  // ----------------------------
  // 登录提交 (POST /login)
  // ----------------------------
  // 表单提交用户名和密码
  svr.Post("/login", [&](const httplib::Request& req, httplib::Response& res) {
    std::string user = req.get_param_value("user");  // 获取表单用户名
    std::string pass = req.get_param_value("pass");  // 获取表单密码

    if (user_db.count(user) && user_db[user] == pass)
    {
      // 登录成功
      std::string token = generate_token();            // 生成 token
      sessions[token] = user;                          // 保存 session
      res.set_header("Set-Cookie", "token=" + token);  // 返回 Cookie 给客户端
      res.set_content("Login success! <a href='/dashboard'>Go to Dashboard</a>", "text/html");
    }
    else
    {
      // 登录失败
      res.set_content("Login failed! <a href='/login'>Try again</a>", "text/html");
    }
  });

  // ----------------------------
  // 受保护资源 (GET /dashboard)
  // ----------------------------
  // 只有登录成功并持有有效 token 的用户才能访问
  svr.Get("/dashboard", [&](const httplib::Request& req, httplib::Response& res) {
    if (!check_session(req))
    {
      // 未登录或 token 无效
      res.status = 403;
      res.set_content("Forbidden. <a href='/login'>Login</a>", "text/html");
      return;
    }
    // 登录成功
    res.set_content("Welcome to Dashboard!", "text/plain");
  });

  // ----------------------------
  // 启动服务
  // ----------------------------
  std::cout << "Server running at http://0.0.0.0:8080\n";
  svr.listen("0.0.0.0", 8080);
}
