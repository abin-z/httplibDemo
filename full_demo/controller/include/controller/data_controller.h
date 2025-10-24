/*
    数据相关Controller接口
*/

#pragma once
#include "base_controller.h"

class DataController : public BaseController
{
 public:
  explicit DataController(httplib::Server& svr) : BaseController(svr) {}

  // 注册路由(父类纯虚函数), 必须重写该方法
  virtual void register_routes() override;

 protected:
  // before_handler 处理前方法(父类虚函数, 根据实际情况重写)
  virtual bool before_handler(const httplib::Request&, httplib::Response&) override;
  // after_handler 处理后方法(父类虚函数, 根据实际情况重写)
  virtual void after_handler(const httplib::Request&, httplib::Response&) override;

 private:
  // 电量与信号记录
  void powerSignalRecord(const httplib::Request& req, httplib::Response& res);
  // 设备信息分页查询
  void deviceOriginalData(const httplib::Request& req, httplib::Response& res);
  // 上报数据记录
  void getCommRecordById(const httplib::Request& req, httplib::Response& res);
};
