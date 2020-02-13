#include <UWUEngine/Systems/LogSys.h>
#include <iostream>

using namespace ColoredOutput;

namespace UWUEngine
{

template <>
LogSys::LogStream& operator<< <char const*>(LogSys::LogStream& ls, char const* const& out)
{
  std::cerr << out;
#ifdef _DEBUG
  * (ls.log_) << Strip(out);
#endif
  return ls;
}

template<>
LogSys::LogStream& operator<< <std::string>(LogSys::LogStream& ls, std::string const& out)
{
  std::cerr << out;
#ifdef _DEBUG
  * (ls.log_) << Strip(out);
#endif
  return ls;
}

template <>
auto LogSys::Tee <bool const&>(bool const& value, char const* name, char const* pretty_function)
{
  std::string tf;
  if (value)
  {
    tf = Set(Green) + "true";
  }
  else
  {
    tf = Set(Crimson) + "false";
  }
  Log(TRACE) << "In function " << Set(White) << pretty_function << ", Value of " << Set(Gray, Navy, Bold) << "bool" << Set() << " " << Set(Yellow) << name << Set() << " is " << tf << Set() << "\n";
  return std::forward<bool const>(value);
}

template <>
auto LogSys::Tee <bool&>(bool& value, char const* name, char const* pretty_function)
{
  return Tee<bool const&>(value, name, pretty_function);
}

}
