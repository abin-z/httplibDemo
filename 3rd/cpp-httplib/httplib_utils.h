/**
 * @file httplib_utils.h
 * @brief cpp-httplib库的工具类
 * @author abin
 * @date 2025-11-17
 */

#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

#include "httplib.h"

namespace httplib_utils
{

struct ParsedURL
{
  std::string scheme;  // http / https
  std::string host;
  uint16_t port;
  std::string path;  // 包含 query

  std::string to_string() const
  {
    std::string result = scheme + "://" + host;
    // 只有在非默认端口时显示端口
    if ((scheme == "http" && port != 80) || (scheme == "https" && port != 443))
    {
      result += ":" + std::to_string(port);
    }
    result += path;
    return result;
  }
};

/**
 * @brief 解析 URL
 * @param url 完整 URL，如 "http://example.com:8080/path?query"
 * @return ParsedURL
 * @throws std::invalid_argument URL 格式错误
 */
inline ParsedURL parse_url(const std::string& url)
{
  ParsedURL result;

  // 1. 找 scheme
  auto scheme_pos = url.find("://");
  if (scheme_pos == std::string::npos)
  {
    throw std::invalid_argument("Invalid URL: missing scheme");
  }
  result.scheme = url.substr(0, scheme_pos);
  std::string rest = url.substr(scheme_pos + 3);

  // 2. 找 path 起始
  auto path_pos = rest.find('/');
  std::string host_port;
  if (path_pos == std::string::npos)
  {
    host_port = rest;
    result.path = "/";
  }
  else
  {
    host_port = rest.substr(0, path_pos);
    result.path = rest.substr(path_pos);
  }

  // 3. 分离 host 和 port
  auto colon_pos = host_port.find(':');
  if (colon_pos == std::string::npos)
  {
    result.host = host_port;
    // 默认端口
    if (result.scheme == "http")
      result.port = 80;
    else if (result.scheme == "https")
      result.port = 443;
    else
      throw std::invalid_argument("Unknown scheme: " + result.scheme);
  }
  else
  {
    result.host = host_port.substr(0, colon_pos);
    std::string port_str = host_port.substr(colon_pos + 1);
    result.port = static_cast<uint16_t>(std::stoi(port_str));
  }

  return result;
}

/**
 * @brief 将 httplib::Result 的错误码转换为可读字符串
 * @param res httplib::Result 对象
 * @return 错误描述字符串
 */
inline std::string httplib_error_string(const httplib::Result& res)
{
  if (res) return "";  // 成功

  const auto err = res.error();
  switch (err)
  {
  case httplib::Error::Connection:
    return "Connection failed";
  case httplib::Error::BindIPAddress:
    return "Bind IP Address failed";
  case httplib::Error::Read:
    return "Read failed";
  case httplib::Error::Write:
    return "Write failed";
  case httplib::Error::ExceedRedirectCount:
    return "Exceeded redirect count";
  case httplib::Error::Canceled:
    return "Request canceled";

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  case httplib::Error::SSLConnection:
    return "SSL connection failed";
  case httplib::Error::SSLLoadingCerts:
    return "SSL cert loading failed";
  case httplib::Error::SSLServerVerification:
    return "SSL verification failed";
  case httplib::Error::SSLServerHostnameVerification:
    return "SSL hostname verification failed";
#endif

  default:
    return "Unknown error (" + std::to_string(static_cast<int>(err)) + ")";
  }
}

}  // namespace httplib_utils
