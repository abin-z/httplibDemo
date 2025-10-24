/*
    Controller层模版代码
*/

#pragma once
#include "base_controller.h"

class TempController : public BaseController
{
  public:
    explicit TempController(httplib::Server& svr) : BaseController(svr) {}

    // 注册路由(父类纯虚函数), 必须重写该方法
    virtual void register_routes() override;

  protected:
    // before_handler 处理前方法(父类虚函数, 根据实际情况重写)
    virtual bool before_handler(const httplib::Request&, httplib::Response&) override;
    // after_handler 处理后方法(父类虚函数, 根据实际情况重写)
    virtual void after_handler(const httplib::Request&, httplib::Response&) override;

  private:
    // 成员函数, 可以用于处理接口响应()
    void mem_func(const httplib::Request& req, httplib::Response& res);
};
