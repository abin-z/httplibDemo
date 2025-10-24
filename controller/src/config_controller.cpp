#include "controller/config_controller.h"

#include <string>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

void ConfigController::register_routes()
{
    register_route(HttpMethod::GET, "/sim/simDeviceParamConfig/getByDeviceId", &ConfigController::getParamConfigByDeviceId);
    register_route(HttpMethod::POST, "/sim/simDeviceParamConfig/updateParamConfig", &ConfigController::updateParamConfig);
}

bool ConfigController::before_handler(const httplib::Request& req, httplib::Response& res)
{
    return true;
}

void ConfigController::after_handler(const httplib::Request& req, httplib::Response& res) {}

void ConfigController::getParamConfigByDeviceId(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}
// 修改参数配置并通知运维平台
void ConfigController::updateParamConfig(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}