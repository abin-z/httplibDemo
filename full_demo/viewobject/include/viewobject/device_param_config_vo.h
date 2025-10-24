#pragma once

#include <nlohmann/json.hpp>
#include <string>

/*
 * 接口名称: 通过设备id查询设备参数配置信息
 * 接口路由: /simDeviceParamConfig/getByDeviceId
 */

// data 对象
struct SimDeviceParamConfigDataVO
{
    std::string id;
    std::string deviceId;
    std::string deviceNo;
    std::string configHtml;
    std::string configJson;
    std::string remark;
    std::string createBy;
    std::string createTime;
    std::string updateBy;
    std::string updateTime;
    std::string delFlag;
    std::string tenantId;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceParamConfigDataVO, id, deviceId, deviceNo, configHtml, configJson, remark,
                                   createBy, createTime, updateBy, updateTime, delFlag, tenantId)

// 顶层
struct SimDeviceParamConfigVO
{
    int code{};
    std::string msg;
    SimDeviceParamConfigDataVO data;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceParamConfigVO, code, msg, data)

// -------------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------

/*
 * 接口名称: 修改参数配置并通知运维平台
 * 接口路由: /simDeviceParamConfig/updateParamConfig
 */

struct SimDeviceParamConfigUpdateVO
{
    std::string id;
    std::string deviceId;
    std::string deviceNo;
    std::string configHtml;
    std::string configJson;
    std::string remark;
    std::string createBy;
    std::string createTime;
    std::string updateBy;
    std::string updateTime;
    std::string delFlag;
    std::string tenantId;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceParamConfigUpdateVO, id, deviceId, deviceNo, configHtml, configJson, remark,
                                   createBy, createTime, updateBy, updateTime, delFlag, tenantId)