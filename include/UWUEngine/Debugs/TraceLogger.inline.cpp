#pragma once
#include <UWUEngine/Debugs/TraceLogger.h>
#include <utility>
#include <UWUEngine/Debugs/ColoredOutput.h>

using namespace ColoredOutput;

template <typename T>
auto TraceLogger::Tee(T&& value, char const* name, char const* pretty_function)
{
  Log(TRACE) << "In function " << Set(White) << pretty_function << Set() << ", Value of " << typeid(T).name() << " " << Set(ColoredOutput::White) << name << ColoredOutput::Set() << " is " << Set(ColoredOutput::White) << value << ColoredOutput::Set() << ".\n";
  return std::forward<T>(value);
}

#pragma region Tee specializations
template <>
auto TraceLogger::Tee<bool>(bool&& value, char const* name, char const* pretty_function);
#pragma endregion 

template <typename T>
auto operator<<(TraceLogger::LogStream& ls, T const& out) -> TraceLogger::LogStream&
{
   std::cerr << out;
#ifdef _DEBUG
   *(ls.log_) << out;
#endif
  return ls;
}

#pragma region operator<< specializations
template <>
TraceLogger::LogStream& operator<< <char const*> (TraceLogger::LogStream& ls, char const* const& out);

template <>
TraceLogger::LogStream& operator<< <std::string> (TraceLogger::LogStream& ls, std::string const& out);
#pragma endregion 