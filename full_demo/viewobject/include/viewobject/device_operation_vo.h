#pragma once

/*
 * 接口名称: 通知设备操作
 * 接口路由: /simDeviceOperation/deviceOperation
 */

#include <nlohmann/json.hpp>
#include <string>

struct SimDeviceOperationVO
{
    std::string deviceNo;
    std::string operationType;
    std::string speed;
    std::string operation;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceOperationVO, deviceNo, operationType, speed, operation)
