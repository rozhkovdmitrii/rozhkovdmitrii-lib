//----------------------------------------------------------------------------------------------------------------------
#ifndef LogH
#define LogH
//----------------------------------------------------------------------------------------------------------------------
#include <sstream>
#include <iostream>
#include <string_view>
//----------------------------------------------------------------------------------------------------------------------
namespace rozhkovdmitrii
{
class LoggedObject
{
public:
  LoggedObject(const std::string_view & loggedObjectName) : _loggedObjectName(loggedObjectName) {};
protected:
  const std::string _loggedObjectName;
};

class Log
{
public:
  enum class Type
  {
      INF,
      WRN,
      ERR,
      DBG,
      TRC
  };
  
  Log(Type type, const std::string_view & loggedObjectName) : _type(type), _loggedObjectName(loggedObjectName)
  {};
  
  ~Log();

  static void setEnabled(Type type, bool enabled)
  {
    switch (type) {
    case Type::INF:
      _isINFEnabled = enabled;
      break;
    case Type::WRN:
      _isWRNEnabled = enabled;
      break;
    case Type::ERR:
      _isERREnabled = enabled;
      break;
    case Type::DBG:
      _isDBGEnabled = enabled;
      break;
    case Type::TRC:
      _isTRCEnabled = enabled;
      break;
    }
  }
  
  template<typename T>
  Log & operator<<(const T & value)
  {
    switch (_type) {
#define CASE(TYPE)                                                                               \
        case Type::TYPE:                                                                         \
          if (!_is##TYPE##Enabled)                                                               \
            return *this;                                                                        \
          break;
    CASE(ERR)
    CASE(DBG)
    CASE(INF)
    CASE(WRN)
    CASE(TRC)
#undef CASE
    }
    _oss << value;
    return *this;
  }

  void static enablePrefixPrinting()
  {
    _isPrefixPrintEnabled = true;
  };
  
private:
  static bool _isINFEnabled;
  static bool _isWRNEnabled;
  static bool _isERREnabled;
  static bool _isDBGEnabled;
  static bool _isTRCEnabled;
  static bool _isPrefixPrintEnabled;
  
  static const std::string RST_ForegroundColor;
  
  static const std::string ERR_ForegroundColor;
  static const std::string INF_ForegroundColor;
  static const std::string WRN_ForegroundColor;
  static const std::string DBG_ForegroundColor;
  static const std::string TRC_ForegroundColor;
  
  Type _type;
  const std::string_view & _loggedObjectName;
  std::ostringstream _oss;
};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
#define TRACE(TYPE) rozhkovdmitrii::Log(rozhkovdmitrii::Log::Type::TYPE, _loggedObjectName)
//----------------------------------------------------------------------------------------------------------------------
#endif //LogH
//----------------------------------------------------------------------------------------------------------------------
