#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/*
 * 接口名称: 上报数据记录
 * 接口路由: /simDeviceOriginalData/getCommRecordById/{id}
 */

// 单条设备数据
struct SimDeviceDataVO
{
    std::string id;
    std::string sensorName;
    std::string interfaceNo;
    std::string interfaceAddr;
    std::string dataTypeCode;
    std::string dataTypeName;
    std::string dataValue;
    std::string dataUnit;
    std::string collectTime;
};

// 序列化宏
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceDataVO, id, sensorName, interfaceNo, interfaceAddr, dataTypeCode,
                                   dataTypeName, dataValue, dataUnit, collectTime)

// data 内部结构
struct GetCommRecordDataVO
{
    std::string jsonData;
    std::vector<SimDeviceDataVO> simDeviceDataListVOList;
};

// 序列化宏
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetCommRecordDataVO, jsonData, simDeviceDataListVOList)

// 顶层返回结构
struct GetCommRecordByIdVO
{
    int code{};
    std::string msg;
    GetCommRecordDataVO data;
};

// 顶层序列化宏
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetCommRecordByIdVO, code, msg, data)
