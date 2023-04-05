#include "LoginTooLong_Exception.h"



LoginTooLong_Exception::LoginTooLong_Exception(const std::string& login,
    size_t maxLength): std::exception()
{
  errorMessage_ += "Error: Login(" + login + ") exceeds MAX_LENGTH(" + std::to_string(maxLength) + ")";
}



const char* LoginTooLong_Exception::what() const noexcept
{
  return errorMessage_.c_str();
}