#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>
#include <sstream>
class Message
{
 public:
  Message() : _message("") { }

  Message(const std::string msg) : _message(msg) { }
  Message(const char* msg) : _message(msg) { }

  std::string str() const
  {
    return _message;
  }

  operator std::string()
  {
    return _message;
  }

  template<typename T>
  Message& operator<<(const T msg)
  {
    std::ostringstream oss;
    oss << msg;
    _message += oss.str();

    return *this;
  }

  private:
  std::string _message;
};

#endif
