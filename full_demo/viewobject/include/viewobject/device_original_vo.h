#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "comm_record_vo.h"

/*
 * 接口名称: 分页查询
 * 接口路由: /simDeviceOriginalData/page
 */

// // 内部数据点
// struct SimDeviceDataVO
// {
//   std::string id;
//   std::string sensorName;
//   std::string interfaceNo;
//   std::string interfaceAddr;
//   std::string dataTypeCode;
//   std::string dataTypeName;
//   std::string dataValue;
//   std::string dataUnit;
//   std::string collectTime;
// };
// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceDataVO, id, sensorName, interfaceNo, interfaceAddr, dataTypeCode,
//                                    dataTypeName, dataValue, dataUnit, collectTime)

// 趋势数据
struct SimDeviceDataTrendVO
{
  std::string collectTime;
  std::string dataValue;
  std::string seriesName;
  std::string unit;
  std::vector<std::string> xData;
  std::vector<std::string> yData;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceDataTrendVO, collectTime, dataValue, seriesName, unit, xData, yData)

// 每条上报记录
struct SimDeviceOriginalDataRecordVO
{
  std::string id;
  std::string deviceNo;
  std::string deviceId;
  std::string deviceIdDeviceName;
  std::string deviceName;
  std::string commTime;
  std::string reportTime;
  int recordCount = 0;
  std::string collectStartTime;
  std::string collectEndTime;
  int collectCount = 0;
  std::string remark;
  std::string createBy;
  std::string createTime;
  std::string updateBy;
  std::string updateTime;
  std::string delFlag;
  std::string tenantId;
  std::string dataTypeCode;
  std::string dataTypeName;
  std::string dataUnit;
  std::vector<SimDeviceDataVO> simDeviceDataListVOList;
  SimDeviceDataTrendVO simDeviceDataTrendVO;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceOriginalDataRecordVO, id, deviceNo, deviceId, deviceIdDeviceName,
                                   deviceName, commTime, reportTime, recordCount, collectStartTime, collectEndTime,
                                   collectCount, remark, createBy, createTime, updateBy, updateTime, delFlag, tenantId,
                                   dataTypeCode, dataTypeName, dataUnit, simDeviceDataListVOList, simDeviceDataTrendVO)

// 分页信息 + records
struct SimDeviceOriginalDataPageVO
{
  std::vector<SimDeviceOriginalDataRecordVO> records;
  int total = 0;
  int size = 0;
  int current = 0;
  struct OrderVO
  {
    std::string column;
    bool asc = true;
  };
  std::vector<OrderVO> orders;
  bool optimizeCountSql = true;
  bool searchCount = true;
  bool optimizeJoinOfCountSql = true;
  int maxLimit = 0;
  std::string countId;
  int pages = 0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceOriginalDataPageVO::OrderVO, column, asc)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceOriginalDataPageVO, records, total, size, current, orders, optimizeCountSql,
                                   searchCount, optimizeJoinOfCountSql, maxLimit, countId, pages)

// 顶层返回 VO
struct SimDeviceOriginalDataVO
{
  int code = 0;
  std::string msg;
  SimDeviceOriginalDataPageVO data;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimDeviceOriginalDataVO, code, msg, data)
