#pragma once
#include "base_controller.h"

class DeviceController : public BaseController
{
  public:
    explicit DeviceController(httplib::Server& svr) : BaseController(svr) {}

    virtual void register_routes() override;

  protected:
    virtual bool before_handler(const httplib::Request&, httplib::Response&) override;
    virtual void after_handler(const httplib::Request&, httplib::Response&) override;

  private:
    // 获取所有状态
    void getAllStatus(const httplib::Request& req, httplib::Response& res);
};
