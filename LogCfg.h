#ifndef LogCfgH
#define LogCfgH
//----------------------------------------------------------------------------------------------------------------------
#include <string_view>
#include <optional>
//----------------------------------------------------------------------------------------------------------------------
#include "Log.h"
//----------------------------------------------------------------------------------------------------------------------
struct LogCfgData
{
  typedef std::optional<Log::Type> OptionalType;
  typedef std::optional<bool> OptionalBool;
  typedef std::optional<std::string> OptionalString;
  
  OptionalType   _logLevel;
  OptionalBool   _console;
  OptionalBool   _syslog;
  OptionalString _filename;
};
//----------------------------------------------------------------------------------------------------------------------
class LogCfg
{
public:
  bool readFromFile(const std::string & fileName);

private:
  LogCfgData _logCfgData;
  
  void parseCfgLine(const std::string_view & cfgLine);
  void applyCfgValue(const std::string_view & key, const std::string_view & value);
  void applyLogLevel(const std::string_view & logLevel);
  void applyConsole(const std::string_view & console);
  void applyFile(const std::string_view & file);
  void applySyslog(const std::string_view & syslog);
  static bool readAsBool(const std::string_view & value);
  static bool splitCfgLine(std::string_view & key, std::string_view & value, const std::string_view & cfgLine);
};
//----------------------------------------------------------------------------------------------------------------------
#endif //LogCfgH
