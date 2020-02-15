#include <catch2/catch.hpp>

#include <UWUEngine/Systems/LogSys.h>

#include <UWUTest/Engine.hpp>
#include <UWUTest/Systems/HeadlessWindowSys.hpp>

using namespace UWUEngine;

namespace
{
  void LogTest(LogSys& logSys)
  {
    std::string logMessage = "This is a Log Message";

    logSys.Log(LogSys::SERIALIZATION) << logMessage << std::endl;
    logSys.Log(LogSys::TRACE) << logMessage << std::endl;
    logSys.Log(LogSys::DEBUG) << logMessage << std::endl;
    logSys.Log(LogSys::INFO) << logMessage << std::endl;
    logSys.Log(LogSys::WARNING) << logMessage << std::endl;
    logSys.Log(LogSys::ERROR) << logMessage << std::endl;
    logSys.Log(LogSys::FAILURE) << logMessage << std::endl << std::endl;

  }
}

TEST_CASE("Trace Logger")
{
  auto * engine = new UWUTest::Engine<LogSys, UWUTest::HeadlessWindowSys>;
  auto& logSys = engine->GetSystems().Get<LogSys>();

  SECTION("Min Severity = SERIALIZATION")
  {
    std::cout << "Min Severity set to " << "SERIALIZATION" << std::endl;
    logSys.SetMinSeverity(LogSys::SERIALIZATION);
    LogTest(logSys);
  }

  SECTION("Min Severity = TRACE")
  {
    std::cout << "Min Severity set to " << "TRACE" << std::endl;
    logSys.SetMinSeverity(LogSys::TRACE);
    LogTest(logSys);
  }

  SECTION("Min Severity = DEBUG")
  {
    std::cout << "Min Severity set to " << "DEBUG" << std::endl;
    logSys.SetMinSeverity(LogSys::DEBUG);
    LogTest(logSys);
  }

  SECTION("Min Severity = INFO")
  {
    std::cout << "Min Severity set to " << "INFO" << std::endl;
    logSys.SetMinSeverity(LogSys::INFO);
    LogTest(logSys);
  }

  SECTION("Min Severity = WARNING")
  {
    std::cout << "Min Severity set to " << "WARNING" << std::endl;
    logSys.SetMinSeverity(LogSys::WARNING);
    LogTest(logSys);
  }

  SECTION("Min Severity = ERROR")
  {
    std::cout << "Min Severity set to " << "ERROR" << std::endl;
    logSys.SetMinSeverity(LogSys::ERROR);
    LogTest(logSys);
  }

  SECTION("Min Severity = FAILURE")
  {
    std::cout << "Min Severity set to " << "FAILURE" << std::endl;
    logSys.SetMinSeverity(LogSys::FAILURE);
    LogTest(logSys);
  }
}
