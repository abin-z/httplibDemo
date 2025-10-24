#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/*
 * 接口名称: 电量与信号记录
 * 接口路由: /simDevicePowerSignalRecord/powerSignalRecord
 */

struct TrendVO
{
  std::string seriesName;
  std::vector<std::string> xData;
  std::vector<double> yData;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TrendVO, seriesName, xData, yData)

struct PowerSignalRecordDataVO
{
  TrendVO signalTrend;
  TrendVO batteryTrend;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PowerSignalRecordDataVO, signalTrend, batteryTrend)

struct PowerSignalRecordVO
{
  int code;
  std::string msg;
  PowerSignalRecordDataVO data;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PowerSignalRecordVO, code, msg, data)
