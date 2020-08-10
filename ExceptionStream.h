#ifndef RDExceptionStreamH
#define RDExceptionStreamH
//----------------------------------------------------------------------------------------------------------------------
#define RD_THROW(ex_type) throw rozhkovdmitrii::ExceptionStream<ex_type>()
//----------------------------------------------------------------------------------------------------------------------
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
namespace rozhkovdmitrii
{
template<typename ExceptionT>
class ExceptionStream : public ExceptionT
{
public:
  ExceptionStream() :
    ExceptionT("")
  {}
  
  ExceptionStream(const ExceptionStream & rhs) :
    ExceptionT(rhs._oss.str())
  {
    _oss << rhs._oss.rdbuf();
  }
  
  ExceptionStream & operator=(const ExceptionStream & rhs)
  {
    if (this == &rhs)
      return *this;
    _oss << rhs._oss.rdbuf();
    ExceptionT::operator=(ExceptionT(_oss.str()));
    return *this;
  }
  
  virtual ~ExceptionStream()
  {}
  
  template<typename T>
  ExceptionStream & operator<<(const T & value)
  {
    _oss << value;
    return *this;
  }

private:
  std::stringstream _oss;
};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
#endif //RDExceptionStreamH
//----------------------------------------------------------------------------------------------------------------------
