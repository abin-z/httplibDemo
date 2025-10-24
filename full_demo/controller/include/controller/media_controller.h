/*
    媒体文件相关的接口
*/

#pragma once
#include "base_controller.h"

class MediaController : public BaseController
{
 public:
  explicit MediaController(httplib::Server& svr) : BaseController(svr) {}

  // 注册路由(父类纯虚函数), 必须重写该方法
  virtual void register_routes() override;

 protected:
  // before_handler 处理前方法(父类虚函数, 根据实际情况重写)
  virtual bool before_handler(const httplib::Request&, httplib::Response&) override;
  // after_handler 处理后方法(父类虚函数, 根据实际情况重写)
  virtual void after_handler(const httplib::Request&, httplib::Response&) override;

 private:
  // 录制媒体管理分页
  void recordingMedia(const httplib::Request& req, httplib::Response& res);

  // 播报文件列表
  void broadcastAudio(const httplib::Request& req, httplib::Response& res);

  // 板端获取平台的广播音频
  void getBroadcastAudio(const httplib::Request& req, httplib::Response& res);
};
