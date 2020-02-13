#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Helper.h>
#include <fstream>
#include <iostream>

#define TEE(x) EXPAND(Get<LogSys>().Tee((x), #x, FUNCTION_SIGNATURE))

namespace UWUEngine
{

class LogSys : public System
{
public:
  class LogStream
  {
  public:
    explicit LogStream(std::ofstream& log);
    LogStream() = default;

    template <typename T>
    friend LogStream& operator<< (LogStream& ls, const T& out);

    friend LogStream& operator<< (LogStream& ls, std::ostream& (*f)(std::ostream&));

    friend class LogSys;
  private:
    void attach(std::ofstream* log);
    std::ofstream* log_;
  };

  LogSys(ISpace*);
  ~LogSys();
  void Update() override;

  enum Severity
  {
    SERIALIZATION,
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FAILURE,
  };

  void SetMinSeverity(Severity level);
  void Assert(bool expression, char const* format, ...);
  int Log(Severity level, char const* format, ...);
  LogStream& Log(Severity level); // TraceLogger::Log(ERROR) << "blah blah c++" << std::endl;

  template <typename T>
  auto Tee(T&& value, char const* name, char const* pretty_function);
private:
  size_t GenTraceUID();
  std::string GetHeader();

  size_t trace_UID = GenTraceUID();
  const size_t stdout_bufsize = 4096;
  char* stdout_buffer = new char[stdout_bufsize];
#ifdef _DEBUG
  Severity min_severity = SERIALIZATION;
#else
  Severity min_severity = WARNING;
#endif
  std::ofstream log_file;
  LogStream log_stream;
  LogStream log_null;
};

}

#include <UWUEngine/Debug/LogSys.inline.cpp> /* Template implementations. */