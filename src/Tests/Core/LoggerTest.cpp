#include <catch2/catch.hpp>

#include <UWUEngine/Systems/LogSys.h>

#include <UWUTest/Engine.hpp>
#include <UWUTest/Systems/HeadlessWindowSys.hpp>

using namespace UWUEngine;

namespace
{
  void LogTest(LogSys& logSys)
  {
    if (false)
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
}

TEST_CASE("Trace Logger")
{
  auto * engine = new UWUTest::Engine<LogSys, UWUTest::HeadlessWindowSys>;
  auto& logSys = engine->GetSystems().Get<LogSys>();

  SECTION("Min Severity = SERIALIZATION")
  {
    INFO("Min Severity set to " << "SERIALIZATION");
    logSys.SetMinSeverity(LogSys::SERIALIZATION);
    LogTest(logSys);
  }

  SECTION("Min Severity = TRACE")
  {
    INFO("Min Severity set to " << "TRACE")
    logSys.SetMinSeverity(LogSys::TRACE);
    LogTest(logSys);
  }

  SECTION("Min Severity = DEBUG")
  {
    INFO("Min Severity set to " << "DEBUG")
    logSys.SetMinSeverity(LogSys::DEBUG);
    LogTest(logSys);
  }

  SECTION("Min Severity = INFO")
  {
    INFO("Min Severity set to " << "INFO")
    logSys.SetMinSeverity(LogSys::INFO);
    LogTest(logSys);
  }

  SECTION("Min Severity = WARNING")
  {
    INFO("Min Severity set to " << "WARNING")
    logSys.SetMinSeverity(LogSys::WARNING);
    LogTest(logSys);
  }

  SECTION("Min Severity = ERROR")
  {
    INFO("Min Severity set to " << "ERROR")
    logSys.SetMinSeverity(LogSys::ERROR);
    LogTest(logSys);
  }

  SECTION("Min Severity = FAILURE")
  {
    INFO("Min Severity set to " << "FAILURE")
    logSys.SetMinSeverity(LogSys::FAILURE);
    LogTest(logSys);
  }

  delete engine;
}
