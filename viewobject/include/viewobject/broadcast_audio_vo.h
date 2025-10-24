#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/*
 * 接口名称: 播报文件列表
 * 接口路由: /simSysBroadcastAudio/broadcastAudioList
 */

// 单个音频文件信息
struct BroadcastAudioVO
{
    std::string id;
    std::string soundType;
    int fileSize{};
    std::string fileUrl;
    std::string operatorId;
    std::string operatorIdName;
    std::string remark;
    std::string createBy;
    std::string createTime;
    std::string updateBy;
    std::string updateTime;
    std::string delFlag;
    std::string tenantId;
    std::string md5;
    std::string syncStatus;
};

// 序列化宏
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BroadcastAudioVO, id, soundType, fileSize, fileUrl, operatorId, operatorIdName,
                                   remark, createBy, createTime, updateBy, updateTime, delFlag, tenantId, md5,
                                   syncStatus)

// 顶层返回 VO
struct BroadcastAudioListVO
{
    int code{};
    std::string msg;
    std::vector<BroadcastAudioVO> data;
};

// 顶层序列化宏
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BroadcastAudioListVO, code, msg, data)
