#include <fstream>
#include <array>
//----------------------------------------------------------------------------------------------------------------------
#include "LogCfg.h"
//----------------------------------------------------------------------------------------------------------------------
bool LogCfg::readFromFile(const std::string & fileName)
{
  std::ifstream ifstream(fileName);
  std::string cfgLine;
  while (std::getline(ifstream, cfgLine))
  {
    parseCfgLine(cfgLine);
  }
  return false;
}
//----------------------------------------------------------------------------------------------------------------------
void LogCfg::parseCfgLine(const std::string_view & cfgLine)
{
  std::string_view key, value;
  if (!splitCfgLine(key, value, cfgLine))
    return;
  applyCfgValue(key, value);
  
}
//----------------------------------------------------------------------------------------------------------------------
bool LogCfg::splitCfgLine(std::string_view & key, std::string_view & value, const std::string_view & cfgLine)
{
  auto delimPos = cfgLine.find_first_of(":");
  if (delimPos == std::string::npos)
    return false;
  key = cfgLine.substr(0, delimPos);
  value = cfgLine.substr(delimPos + 1);
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
void LogCfg::applyCfgValue(const std::string_view & key, const std::string_view & value)
{
  if ("level" == key)
    applyLogLevel(value);
  else if ("console" == key)
    applyConsole(value);
  else if ("file" == key)
    applyFile(value);
  else if ("syslog" == key)
    applySyslog(value);
}
//----------------------------------------------------------------------------------------------------------------------
void LogCfg::applyLogLevel(const std::string_view & logLevel)
{
  if ("INF" == logLevel)
    _logCfgData._logLevel = Log::Type::INF;
  else if ("ERR" == logLevel)
    _logCfgData._logLevel = Log::Type::ERR;
  else if ("WRN" == logLevel)
    _logCfgData._logLevel = Log::Type::WRN;
  else if ("DBG" == logLevel)
    _logCfgData._logLevel = Log::Type::DBG;
  else if ("TRC" == logLevel)
    _logCfgData._logLevel = Log::Type::TRC;
  else if ("DAT" == logLevel)
    _logCfgData._logLevel = Log::Type::DAT;

  if (!_logCfgData._logLevel.has_value())
    return;
  
  switch (_logCfgData._logLevel.value())
  {
#define CASE(LEVEL)                          \
  case Log::Type::LEVEL:                     \
    Log::setEnabled(Log::Type::LEVEL, true);
  CASE(ERR)
  CASE(WRN)
  CASE(INF)
  CASE(DBG)
  CASE(TRC)
  CASE(DAT)
#undef CASE

  }
}
//----------------------------------------------------------------------------------------------------------------------
void LogCfg::applyConsole(const std::string_view & console)
{
  _logCfgData._console = readAsBool(console);
}
//----------------------------------------------------------------------------------------------------------------------
void LogCfg::applyFile(const std::string_view & file)
{
  _logCfgData._filename = file;
}
//----------------------------------------------------------------------------------------------------------------------
void LogCfg::applySyslog(const std::string_view & syslog)
{
  _logCfgData._syslog = readAsBool(syslog);
}
//----------------------------------------------------------------------------------------------------------------------
namespace
{
bool iequals(const std::string_view & left, const std::string_view & right)
{
  return std::equal(left.begin(), left.end(), right.begin(),
                    [](char a, char b) {
                      return tolower(a) == tolower(b);
                    });
}
}
//----------------------------------------------------------------------------------------------------------------------
bool LogCfg::readAsBool(const std::string_view & value)
{
  return (iequals(value, "yes") || iequals(value, "true") || iequals(value, "on") || iequals(value, "1"));
}
//----------------------------------------------------------------------------------------------------------------------
