#pragma once
#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/Helper.h>
#include <fstream>

#define TEE(x) EXPAND(TraceLogger::Tee((x), #x, FUNCTION_SIGNATURE))

class TraceLogger : public BaseSystem<TraceLogger>
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

    friend class TraceLogger;
  private:
    void attach(std::ofstream* log);
    std::ofstream* log_;
  };

  TraceLogger();
  ~TraceLogger();
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

  static void SetMinSeverity(Severity level);
  static void Assert(bool expression, char const* format, ...);
  static int Log(Severity level, char const* format, ...);
  static LogStream& Log(Severity level); // TraceLogger::Log(ERROR) << "blah blah c++" << std::endl;

  template <typename T>
  static auto Tee(T&& value, char const* name, char const* pretty_function);
private:
  static size_t GenTraceUID();
  static std::string GetHeader();

  static size_t trace_UID;
  static char* stdout_buffer;
  static Severity min_severity;
  static std::ofstream log_file;
  static LogStream log_stream;
  static LogStream log_null;
};

#include "TraceLogger.inline.cpp" /* Template implementations. */