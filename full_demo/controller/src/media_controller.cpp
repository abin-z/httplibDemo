#include "controller/media_controller.h"

#include <string>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

void MediaController::register_routes()
{
    register_route(HttpMethod::GET, "/sim/simDeviceRecordingFile/recordingMediaPage", &MediaController::recordingMedia);
    register_route(HttpMethod::GET, "/sim/simSysBroadcastAudio/broadcastAudioList", &MediaController::broadcastAudio);
    register_route(HttpMethod::POST, "/sim/simDeviceOperation/getBroadcastAudioList", &MediaController::getBroadcastAudio);
}

bool MediaController::before_handler(const httplib::Request& req, httplib::Response& res)
{
    return true;
}

void MediaController::after_handler(const httplib::Request& req, httplib::Response& res) {}

void MediaController::recordingMedia(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}

void MediaController::broadcastAudio(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}

void MediaController::getBroadcastAudio(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json j;
    j["msg"] = "ok";
    j["code"] = 200;
    std::string json_str = j.dump();
    res.set_content(json_str, "application/json");
}