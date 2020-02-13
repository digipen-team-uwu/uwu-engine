#pragma once
#include <stdexcept>
#include <typeinfo>
#include <string>

template<typename T>
class SystemStartupException : public std::runtime_error
{
public:
  SystemStartupException() :
  runtime_error(std::string(typeid(T).name()) + " System failed to start.") {}
};