#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/*
接口名称: 设备详情
接口路由: /simDevice/getInfo/{id}
*/

struct SimDeviceTriaxialDataVO
{
    std::string x;
    std::string y;
    std::string z;
    std::string status;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceTriaxialDataVO, x, y, z, status)

struct SimDeviceInfoDataExtendVO
{
    std::string id;
    std::string deviceId;
    std::string interfaceType;
    std::string interfaceTypeLabel;
    std::string interfaceNo;
    std::string interfaceAddr;
    std::string sensorCode;
    std::string alarmType;
    std::string alarmTypeLabel;
    std::string sourceType;
    std::string dataTypeCode;
    std::string dataValue;
    std::string collectTime;
    std::string remark;
    std::string createBy;
    std::string createTime;
    std::string updateBy;
    std::string updateTime;
    std::string delFlag;
    std::string tenantId;
    std::string dataTypeName;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceInfoDataExtendVO, id, deviceId, interfaceType, interfaceTypeLabel,
                                   interfaceNo, interfaceAddr, sensorCode, alarmType, alarmTypeLabel, sourceType,
                                   dataTypeCode, dataValue, collectTime, remark, createBy, createTime, updateBy,
                                   updateTime, delFlag, tenantId, dataTypeName)

struct SimDeviceFileInferenceExtendVO
{
    std::string id;
    std::string recordingFileId;
    std::string inferencePositionType;
    std::string inferencePositionTypeLabel;
    std::string inferenceResult;
    std::string inferenceTime;
    double x1{0.0};
    double y1{0.0};
    double x2{0.0};
    double y2{0.0};
    double score{0.0};
    std::string remark;
    std::string createBy;
    std::string createTime;
    std::string updateBy;
    std::string updateTime;
    std::string delFlag;
    std::string tenantId;
    std::string recognitionType;
    std::string recognitionTypeLabel;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceFileInferenceExtendVO, id, recordingFileId, inferencePositionType,
                                   inferencePositionTypeLabel, inferenceResult, inferenceTime, x1, y1, x2, y2, score,
                                   remark, createBy, createTime, updateBy, updateTime, delFlag, tenantId,
                                   recognitionType, recognitionTypeLabel)

struct SimDeviceInfoShowVO
{
    std::string id;
    std::string deviceId;
    std::string imagingMode;
    std::string imagingModeLabel;
    std::string whiteLightType;
    std::string whiteLightTypeLabel;
    std::string redLightType;
    std::string redLightTypeLabel;
    std::string networkSignalType;
    std::string satelliteSignalType;
    std::string networkSignalTypeLabel;
    std::string satelliteSignalTypeLabel;
    std::string commSignalType;
    std::string commSignalTypeLabel;
    std::string mainStreamResolution;
    std::string workMode;
    std::string workModeLabel;
    std::string imageRecognitionMode;
    std::string imageRecognitionModeLabel;
    std::string voiceprintMode;
    std::string voiceprintModeLabel;
    std::string continuousRunningTime;
    double power{0.0};
    std::string remainingStorage;
    std::string triggerType;
    std::string triggerTypeLabel;
    std::string remark;
    SimDeviceTriaxialDataVO acceleration;
    SimDeviceTriaxialDataVO gyroscope;
    std::vector<SimDeviceInfoDataExtendVO> simDeviceInfoDataExtendVOList;
    std::vector<SimDeviceFileInferenceExtendVO> simDeviceRecordingFileExtendVOList;
    std::string deviceName;
    std::string lastCommTime;
    std::string deviceNo;
    std::string version;
    std::string streamUrl;
    std::string videoStatus;
    std::string videoStatusLabel;
    std::string recordingStatus;
    std::string recordingStatusLabel;
    std::string intercomStatus;
    std::string intercomStatusLabel;
    std::string broadcastStatus;
    std::string broadcastStatusLabel;
    std::string audioVisualAlarmStatus;
    std::string audioVisualAlarmStatusLabel;
    std::string currentTriggerType;
    std::string mapPosition;
    std::string satelliteLongitude;
    std::string satelliteLatitude;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceInfoShowVO, id, deviceId, imagingMode, imagingModeLabel, whiteLightType,
                                   whiteLightTypeLabel, redLightType, redLightTypeLabel, networkSignalType,
                                   satelliteSignalType, networkSignalTypeLabel, satelliteSignalTypeLabel,
                                   commSignalType, commSignalTypeLabel, mainStreamResolution, workMode, workModeLabel,
                                   imageRecognitionMode, imageRecognitionModeLabel, voiceprintMode, voiceprintModeLabel,
                                   continuousRunningTime, power, remainingStorage, triggerType, triggerTypeLabel,
                                   remark, acceleration, gyroscope, simDeviceInfoDataExtendVOList,
                                   simDeviceRecordingFileExtendVOList, deviceName, lastCommTime, deviceNo, version,
                                   streamUrl, videoStatus, videoStatusLabel, recordingStatus, recordingStatusLabel,
                                   intercomStatus, intercomStatusLabel, broadcastStatus, broadcastStatusLabel,
                                   audioVisualAlarmStatus, audioVisualAlarmStatusLabel, currentTriggerType, mapPosition,
                                   satelliteLongitude, satelliteLatitude)

struct SimDeviceInfoVO
{
    int code;
    std::string msg;
    SimDeviceInfoShowVO data;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceInfoVO, code, msg, data)
