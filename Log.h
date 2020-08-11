//----------------------------------------------------------------------------------------------------------------------
#ifndef RDLogH
#define RDLogH
//----------------------------------------------------------------------------------------------------------------------
#include <sstream>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
namespace rozhkovdmitrii
{
class Log
{
public:
  enum class Type
  {
    DBG,
    INF,
    WRN,
    ERR,
  };
  
  Log(Type type) : _type(type)
  {};
  
  ~Log()
  {
    switch (_type)
    {
#define CASE(TYPE)                         \
    case Type::TYPE:                       \
      if (!_is##TYPE##Enabled)             \
      break;                               \
      if (_isPrefixPrintEnabled)           \
        std::cout << "##TYPE##: ";         \
      std::cout << _oss.str() << std::endl;\
      break;
    CASE(DBG)
    CASE(INF)
    CASE(WRN)
    CASE(ERR)
#undef CASE
    }
  }
  
  static void setEnabled(Type type, bool enabled)
  {
    switch (type)
    {
    case Type::DBG:
      _isDBGEnabled = enabled;
      break;
    case Type::INF:
      _isINFEnabled = enabled;
      break;
    case Type::WRN:
      _isWRNEnabled = enabled;
      break;
    case Type::ERR:
      _isERREnabled = enabled;
      break;
    }
  }
  
  template<typename T>
  Log & operator<<(const T & value)
  {
    _oss << value;
    return *this;
  }

  void static enablePrefixPrinting()
  {
    _isPrefixPrintEnabled = true;
  };
  
private:
  static bool _isINFEnabled;
  static bool _isDBGEnabled;
  static bool _isWRNEnabled;
  static bool _isERREnabled;
  static bool _isPrefixPrintEnabled;
  
  Type _type;
  std::ostringstream _oss;
};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
#define RD_LOG(TYPE) rozhkovdmitrii::Log(rozhkovdmitrii::Log::Type::TYPE)
//----------------------------------------------------------------------------------------------------------------------
#endif //RDLogH
//----------------------------------------------------------------------------------------------------------------------
