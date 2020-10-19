//----------------------------------------------------------------------------------------------------------------------
#include <chrono>
#include <iomanip>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
#include "Log.h"
//----------------------------------------------------------------------------------------------------------------------


namespace
{
template<std::size_t V, std::size_t C = 0, typename std::enable_if<(V < 10), int>::type = 0>
constexpr std::size_t log10() {
  return C;
}

template<std::size_t V, std::size_t C = 0, typename std::enable_if<(V >= 10), int>::type = 0>
constexpr std::size_t log10() {
  return log10<V / 10, C + 1>();
}

template<class Precision = std::chrono::seconds, class Clock = std::chrono::system_clock>
class log_watch
{
public:
  using precision_type = Precision;
  using ratio_type = typename precision_type::period;
  static constexpr auto decimal_width = log10<ratio_type{}.den>();
  
  static_assert(ratio_type{}.num <= ratio_type{}.den, "Only second or sub second precision supported");
  static_assert(ratio_type{}.num == 1, "Unsupported precision parameter");
  
  log_watch(const std::string & format = "%FT%T") : m_format(format) {}
  
  template<class P, class C>
  friend std::ostream & operator<<(std::ostream &, const log_watch<P, C> &);

private:
  std::string m_format;
};

template<class Precision, class Clock>
std::ostream& operator<<(std::ostream& os, const log_watch<Precision, Clock>& lw) {
  auto time_point = Clock::now();
  std::time_t t = Clock::to_time_t(time_point);
  os << std::put_time(std::localtime(&t), lw.m_format.c_str());
  
  if(lw.decimal_width) {
    auto dur = time_point.time_since_epoch();
    auto ss = std::chrono::duration_cast<Precision>(dur) % std::chrono::seconds{1};
    os << std::setfill('0') << std::setw(lw.decimal_width) << ss.count();
  }
  return os;
}
}


namespace rozhkovdmitrii
{
//----------------------------------------------------------------------------------------------------------------------
bool Log::_isINFEnabled = true;
bool Log::_isWRNEnabled = true;
bool Log::_isERREnabled = true;
bool Log::_isDBGEnabled = false;
bool Log::_isTRCEnabled = false;
bool Log::_isPrefixPrintEnabled = true;

const std::string Log::ERR_ForegroundColor = "\x1B[31m";
const std::string Log::INF_ForegroundColor = "\x1B[32m";
const std::string Log::WRN_ForegroundColor = "\x1B[33m";
const std::string Log::DBG_ForegroundColor = "\x1B[37m";
const std::string Log::TRC_ForegroundColor = "\x1B[37m";

const std::string Log::RST_ForegroundColor = "\x1B[0m";

Log::~Log() {
  ::log_watch<std::chrono::milliseconds , std::chrono::high_resolution_clock> milli("%D %T.");
  switch (_type) {
#define CASE(TYPE)                                                                           \
    case Type::TYPE:                                                                         \
      if (!_is##TYPE##Enabled)                                                               \
        break;                                                                               \
      std::cout << TYPE##_ForegroundColor;                                                   \
      if (_isPrefixPrintEnabled)                                                             \
        std::cout << "[" << milli << "]" << '\t' << #TYPE << '\t';                                  \
      std::cout << std::setw(20) << std::setfill(' ') << _loggedObjectName << '\t'           \
                << _oss.str() << RST_ForegroundColor << std::endl;                           \
      break;
  CASE(ERR)
  CASE(INF)
  CASE(WRN)
  CASE(DBG)
  CASE(TRC)
#undef CASE
  }
}
}
//----------------------------------------------------------------------------------------------------------------------
