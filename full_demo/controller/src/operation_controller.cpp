#include "controller/operation_controller.h"

#include <string>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

void OperationController::register_routes()
{
    register_route(HttpMethod::POST, "/sim/simDeviceOperation/deviceOperation", &OperationController::deviceOperation);
}

bool OperationController::before_handler(const httplib::Request& req, httplib::Response& res)
{
    return true;
}

void OperationController::after_handler(const httplib::Request& req, httplib::Response& res) {}

void OperationController::deviceOperation(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}