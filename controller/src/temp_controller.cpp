#include "controller/temp_controller.h"

#include <string>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

void TempController::register_routes()
{
    register_route(HttpMethod::GET, "/temp", &TempController::mem_func);
}

bool TempController::before_handler(const httplib::Request& req, httplib::Response& res)
{
    return true;
}

void TempController::after_handler(const httplib::Request& req, httplib::Response& res) {}

void TempController::mem_func(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}