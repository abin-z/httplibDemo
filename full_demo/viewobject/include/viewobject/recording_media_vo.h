#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/*
 * 接口名称: 录制媒体管理分页
 * 接口路由: /simDeviceRecordingFile/recordingMediaPage
 */

// 排序字段
struct OrderVO
{
  std::string column;
  bool asc;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(OrderVO, column, asc)

// 单条录制媒体记录
struct RecordingMediaRecordVO
{
  std::string id;
  std::string fileSourceType;
  std::string fileSourceTypeLabel;
  std::string deviceId;
  std::string deviceIdDeviceName;
  std::string operatorId;
  std::string fileFormat;
  std::string fileFormatLabel;
  std::string recordType;
  std::string recordTypeLabel;
  int fileSize;
  std::string fileUrl;
  std::string originalFileUrl;
  std::string collectDataId;
  std::string triggerType;
  std::string triggerTypeLabel;
  std::string commTime;
  std::string remark;
  std::string createBy;
  std::string createTime;
  std::string updateBy;
  std::string updateTime;
  std::string delFlag;
  std::string tenantId;
  std::string deviceInferenceResult;
  std::string platformInferenceResult;
  std::string deviceName;
  std::string operatorName;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RecordingMediaRecordVO, id, fileSourceType, fileSourceTypeLabel, deviceId,
                                   deviceIdDeviceName, operatorId, fileFormat, fileFormatLabel, recordType,
                                   recordTypeLabel, fileSize, fileUrl, originalFileUrl, collectDataId, triggerType,
                                   triggerTypeLabel, commTime, remark, createBy, createTime, updateBy, updateTime,
                                   delFlag, tenantId, deviceInferenceResult, platformInferenceResult, deviceName,
                                   operatorName)

// data 部分（分页）
struct RecordingMediaPageDataVO
{
  std::vector<RecordingMediaRecordVO> records;
  int total;
  int size;
  int current;
  std::vector<OrderVO> orders;
  bool optimizeCountSql;
  bool searchCount;
  bool optimizeJoinOfCountSql;
  int maxLimit;
  std::string countId;
  int pages;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RecordingMediaPageDataVO, records, total, size, current, orders, optimizeCountSql,
                                   searchCount, optimizeJoinOfCountSql, maxLimit, countId, pages)

// 顶层响应 ✅ 用 VO 结尾
struct RecordingMediaPageVO
{
  int code;
  std::string msg;
  RecordingMediaPageDataVO data;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RecordingMediaPageVO, code, msg, data)
