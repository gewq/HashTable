#include "EmptyString_Exception.h"



EmptyString_Exception::EmptyString_Exception():
  std::exception()
{
  errorMessage_ += "Error: String is empty!";
}



const char* EmptyString_Exception::what() const noexcept
{
  return errorMessage_.c_str();
}