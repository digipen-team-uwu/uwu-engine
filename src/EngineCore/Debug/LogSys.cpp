#include <UWUEngine/Systems/LogSys.h>
#include <string>
#include <cstdarg>
#include <cassert>
#include <clocale>
#include <UWUEngine/Debug/ColoredOutput.h>
#include <magic_enum.hpp>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <UWUEngine/Helper.h>

#include <UWUEngine/PlatformSpecificDefinitions.h>
#include <UWUEngine/PlatformSpecific.h>

#include <memory>
#include <filesystem>
#include <iostream>

#include <UWUEngine/Debug/LogSys.specialization.cpp>
#include <UWUEngine/EngineSettings.h>

namespace UWUEngine
{

LogSys::LogStream::LogStream(std::ofstream& log, bool isNull)
  :
  log_(&log), isNull(isNull)
{

};

void LogSys::LogStream::attach(std::ofstream* log)
{
  log_ = log;
}

LogSys::LogStream& operator<< (LogSys::LogStream& ls, std::ostream& (*f)(std::ostream&))
{
  if (ls.isNull)
  {
    return ls;
  }
  f(std::cerr);
  f(*(ls.log_));
  return ls;
}

using namespace ColoredOutput;

namespace
{
std::string string_format(char const* format, std::va_list args)
{
  std::va_list args_copy;
  va_copy(args_copy, args);
  int const length = std::vsnprintf(nullptr, 0, format, args) + 1;
  va_end(args);
  if (length <= 0)
  {
    // TODO: remove temp exception
    throw std::runtime_error("Error during formatting.");
  }
  std::unique_ptr<char[]> buf(new char[length]);
  std::vsnprintf(buf.get(), length, format, args_copy);
  return std::string(buf.get(), buf.get() + length - 1);
}

std::string string_format(char const* format, ...)
{
  std::va_list args;
  va_start(args, format);
  std::string formatted = string_format(format, args);
  va_end(args);
  return formatted;
}

Color severity_colors[] =
{
  Blue,       // SERIALIZATION
  Aqua,       // TRACE
  Green,      // DEBUG
  Lime,       // INFO
  Yellow,     // WARNING
  Red,        // ERROR
  Crimson,    // FAILURE
};
}

LogSys::LogSys(ISpace* p) : System(p), log_null(true)
{
  if (EngineSettings::Test)
  {
    SetMinSeverity(WARNING);
  }

#ifdef _DEBUG
#ifdef _MSVC
  std::wstringstream log_filepath;
  wchar_t* path = 0;
  SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
  log_filepath << path << L"\\DigiPen";
  _wmkdir(log_filepath.str().c_str());
  log_filepath << L"\\Umbra";
  _wmkdir(log_filepath.str().c_str());
  log_filepath << L"\\logs";
  _wmkdir(log_filepath.str().c_str());
  CoTaskMemFree(static_cast<void*>(path));
  log_filepath << L"/log-" << std::to_wstring(trace_UID) + L".trace";
#else
  std::stringstream log_filepath;
  log_filepath << "./logs";
  log_filepath << "/log-" << std::to_string(trace_UID) + ".trace";
  if (!std::filesystem::exists(std::filesystem::path("./logs/")))
  {
    std::filesystem::create_directory(std::filesystem::path("./logs/"));
  }
#endif
  /* Make log file output unbuffered. Slower, but allows capture of errors that might otherwise be hidden due to buffering. */
  log_file.rdbuf()->pubsetbuf(nullptr, 0);

  log_file.open(log_filepath.str());
#endif

  log_stream.attach(&log_file);
  log_null.attach(&non_std::cnull);

#ifdef _DEBUG
  Assert(log_file.is_open(), "Log file %s opened successfully.", log_filepath.str().c_str());
#endif

  // Set the program's output to use UTF-8
  std::setlocale(LC_ALL, "en_US.UTF-8");
  // Enable synchronization with C stdio functions
  std::ios_base::sync_with_stdio(true);

  std::setvbuf(stdout, stdout_buffer, _IOFBF, stdout_bufsize);
#ifdef _MSVC

  if (IsDebuggerPresent())
  {
    GetSetColorEnabled(false, true);
    if (min_severity < WARNING)
    {
      std::clog << "Welcome " << "Team U" << Set(Pink) << "." << Set() << "W" << Set(Pink) << "." << Set() << "U" << Set() << " developer.\n";
    }
  }
  else
  {
    try
    {
      if (RegGetDword(HKEY_CURRENT_USER, "Console", "VirtualTerminalLevel") == 0x1)
      {
        GetSetColorEnabled(false, true);
      }
    }
    catch (std::exception)
    {
      GetSetColorEnabled(false, false);
    }
  }

#else
  /* Assume other operating systems have color terminals enabled by default. */
  GetSetColorEnabled(false, true);
#endif
  bool const color_enabled = GetSetColorEnabled(true, false);
  bool happy = false;
  if (color_enabled)
  {
    Log(INFO) << Set(White) << "Full color support detected." << Set() << "\n";
  }
  else
  {
    Log(INFO) << "No color support detected - falling back to black and white." << "\n";
  }

  //std::cerr << GetHeader();

  //TEE(color_enabled);
  //TEE(happy);

  // Disable synchronization with C stdio functions
  std::ios_base::sync_with_stdio(false);
  std::setvbuf(stdout, stdout_buffer, _IOLBF, stdout_bufsize);
  Log(INFO) << "my name a jeff" << std::endl;
}

LogSys::~LogSys()
{
  try
  {
    log_file.close();
  }
  catch (...)
  {
    /* :) */
  }
}

void LogSys::Update()
{
  log_file.flush();
}

void LogSys::SetMinSeverity(Severity level)
{
  min_severity = level;
}

void LogSys::Assert(bool expression, char const* format, ...)
{
  std::va_list args;
  if (expression)
  {
    va_start(args, format);
    Log(DEBUG) << "Asserted that " << string_format(format, args) << "\n";
    va_end(args);
  }
  else
  {
    va_start(args, format);
    Log(FAILURE) << "Failed to assert that " << string_format(format, args) << "\n";
    va_end(args);
    assert(expression);
  }
}

int LogSys::Log(Severity level, char const* format, ...)
{
  std::va_list args;
  va_start(args, format);
  std::string const message = string_format(format, args);
  va_end(args);
  Log(level) << message;
  return static_cast<int>(message.length());
}

LogSys::LogStream& LogSys::Log(Severity level)
{
  if (level >= min_severity)
  {
    // console
    std::cerr << "[" << Set(severity_colors[level]) << magic_enum::enum_name(level) << Set() << "]: ";


    // file
    if (log_file.is_open() && !log_file.fail())
    {
      log_file << "[" << magic_enum::enum_name(level) << "]: ";
    }

    return log_stream;
  }
  // lol
  return log_null;
}

size_t LogSys::GenTraceUID()
{
  /* Get the current time. */
  const std::time_t current_time = std::time(nullptr);
  /* */
  size_t trace_UID = (current_time << 32);
#ifdef _WIN64
  trace_UID |= (GetCurrentProcessId() & 0xFFF);
#elif defined(__unix__)
  trace_UID |= (getpid() & 0xFFF);
#endif
  trace_UID |= (__TIME__[7] & 0xFF000);
  return trace_UID;
}

std::string LogSys::GetHeader()
{
  std::stringstream header;

  for (int i = 0; i < 10; ++i)
  {
    for (int j = 0; j < 80; ++j)
    {
      header << Set(glm::vec3{ 1.f - j / 80.f , 0.f, i / 10.f }) << u8"\u2588";
    }
    header << "\n";
  }

  return header.str();
}

}
