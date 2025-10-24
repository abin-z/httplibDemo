#include "controller/data_controller.h"

#include <string>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

void DataController::register_routes()
{
    register_route(HttpMethod::GET, "/sim/simDevicePowerSignalRecord/powerSignalRecord", &DataController::powerSignalRecord);
    register_route(HttpMethod::GET, "/sim/simDeviceOriginalData/page", &DataController::deviceOriginalData);
    register_route(HttpMethod::GET, R"(/sim/simDeviceOriginalData/getCommRecordById/([A-Za-z0-9_-]+))", &DataController::getCommRecordById);
}

bool DataController::before_handler(const httplib::Request& req, httplib::Response& res)
{
    return true;
}

void DataController::after_handler(const httplib::Request& req, httplib::Response& res) {}

// 
void DataController::powerSignalRecord(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}

void DataController::deviceOriginalData(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}

void DataController::getCommRecordById(const httplib::Request& req, httplib::Response& res)
{
    std::string id = req.matches[1];  // get请求的路径id
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}