#include "controller/device_controller.h"

#include <string>

#include "viewobject/device_info_vo.h"
#include "fmt/base.h"
#include "fmt/core.h"
#include "nlohmann/json_fwd.hpp"

void DeviceController::register_routes()
{
    register_route(HttpMethod::GET, R"(/sim/simDevice/getInfo/([A-Za-z0-9_-]+))", &DeviceController::getAllStatus);
}

bool DeviceController::before_handler(const httplib::Request& req, httplib::Response& res)
{
    fmt::println("=== before_handler() ===");
    fmt::println("Method: {}", req.method);
    fmt::println("Path:   {}", req.path);
    fmt::println("Query:  {}", req.params.empty() ? "<none>" : "");

    for (auto& p : req.params) fmt::println("    {} = {}", p.first, p.second);

    fmt::println("Headers:");
    for (auto& h : req.headers) fmt::println("    {}: {}", h.first, h.second);

    if (!req.body.empty()) fmt::println("Body:\n{}", req.body);

    // 模拟登录拦截
    // return false 会让请求被拦截，不进入 handler
    bool authorized = true;  // 这里可以根据 header/cookie 判断登录
    if (!authorized)
    {
        res.status = 401;
        res.set_content("{\"error\":\"Unauthorized\"}", "application/json");
        fmt::println("Request blocked: Unauthorized.");
        return false;
    }

    return true;
}

void DeviceController::after_handler(const httplib::Request& req, httplib::Response& res)
{
    fmt::println("=== after_handler() ===");
    fmt::println("Response status: {}", res.status);
    fmt::println("Response content length: {}", res.body.size());
}

void DeviceController::getAllStatus(const httplib::Request& req, httplib::Response& res)
{
    std::string id = req.matches[1]; // 路径id
    fmt::println("=== getAllStatus() ===");
    fmt::println("Handling request to: {}", req.path);

    SimDeviceInfoVO response;
    response.msg = "oook";
    response.code = 2000;

    nlohmann::json j = response;
    std::string json_str = j.dump();

    // 返回给前端
    res.set_content(json_str, "application/json");
}