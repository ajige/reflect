#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include "message.h"

#define ReflectException(xxx)  ReflectionException( Message(__func__) <<": "<< __LINE__<< ": " << xxx)
//#define ReflectException(xxx)  ReflectionException(xxx)

class ReflectionException
{
 public:
  ReflectionException(const Message &msg)
  {
    _message = msg.str();
  }
  const char*  what() const throw()
  {
    return _message.c_str();
  }
  ~ReflectionException() throw() {}

 protected:
  std::string  _message;
};

#endif
