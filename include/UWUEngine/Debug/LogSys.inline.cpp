#pragma once
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Debug/ColoredOutput.h>
#include <iostream>

using namespace ColoredOutput;

namespace UWUEngine
{

template <typename T>
auto LogSys::Tee(T&& value, char const* name, char const* pretty_function)
{
  Log(TRACE) << "In function " << Set(White) << pretty_function << Set() << ", Value of " << typeid(T).name() << " " << Set(White) << name << Set() << " is " << Set(White) << value << Set() << ".\n";
  return std::forward<T>(value);
}

#pragma region Tee specializations
template <>
auto LogSys::Tee<bool>(bool&& value, char const* name, char const* pretty_function);
#pragma endregion 

template<typename T>
LogSys::LogStream& operator<<(LogSys::LogStream& ls, const T& out)
{
  std::cerr << out;
#ifdef _DEBUG
  * (ls.log_) << out;
#endif
  return ls;
}

#pragma region operator<< specializations
template <>
LogSys::LogStream& operator<< <char const*> (LogSys::LogStream& ls, char const* const& out);

template <>
LogSys::LogStream& operator<< <std::string> (LogSys::LogStream& ls, std::string const& out);
#pragma endregion 

}