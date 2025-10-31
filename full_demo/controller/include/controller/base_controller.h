#pragma once
#include <httplib.h>

#include <string>

#ifdef DELETE
#undef DELETE
#endif

enum class HttpMethod
{
  GET,
  POST,
  PUT,
  DELETE,
  PATCH,
  OPTIONS
};

class BaseController
{
 public:
  explicit BaseController(httplib::Server& svr) : svr_(svr) {}
  virtual ~BaseController() {}

  // 纯虚函数：子类实现注册路由
  virtual void register_routes() = 0;

 protected:
  httplib::Server& svr_;

  // 成员函数路由注册模板, 方便注册成员函数
  template <typename T>
  void register_route(HttpMethod method, const std::string& path,
                      void (T::*handler)(const httplib::Request&, httplib::Response&))
  {
    auto lambda = [this, handler](const httplib::Request& req, httplib::Response& res) {
      // before_handler 可拦截 handler
      if (!this->before_handler(req, res)) return;

      // 执行 handler
      (static_cast<T*>(this)->*handler)(req, res);

      // after_handler
      this->after_handler(req, res);
    };

    switch (method)
    {
    case HttpMethod::GET:
      svr_.Get(path, lambda);
      break;
    case HttpMethod::POST:
      svr_.Post(path, lambda);
      break;
    case HttpMethod::PUT:
      svr_.Put(path, lambda);
      break;
    case HttpMethod::DELETE:
      svr_.Delete(path, lambda);
      break;
    case HttpMethod::PATCH:
      svr_.Patch(path, lambda);
      break;
    case HttpMethod::OPTIONS:
      svr_.Options(path, lambda);
      break;
    default:
      break;
    }
  }

  // handler 前filter,可拦截 handler. 返回ture继续执行
  virtual bool before_handler(const httplib::Request&, httplib::Response&)
  {
    return true;
  }

  // handler 后filter,可做统计工作
  virtual void after_handler(const httplib::Request&, httplib::Response&) {}
};
