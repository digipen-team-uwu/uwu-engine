#include <UWUEngine/Systems/Order.h>

#include <UWUTest/Systems/HeadlessWindowSys.hpp>
#include <UWUTest/Systems/LockedFrameLimiterSys.hpp>

namespace UWUEngine
{
  template <>
  SystemOrder GetSystemOrder<UWUTest::HeadlessWindowSys>()
  {
    return SystemOrder::Window;
  }

#pragma region LockedFrameLimiterSys
  template <>
  SystemOrder GetSystemOrder<UWUTest::LockedFrameLimiterSys<5>>()
  {
    return SystemOrder::FrameLimiter;
  }

  template <>
  SystemOrder GetSystemOrder<UWUTest::LockedFrameLimiterSys<30>>()
  {
    return SystemOrder::FrameLimiter;
  }

  template <>
  SystemOrder GetSystemOrder<UWUTest::LockedFrameLimiterSys<60>>()
  {
    return SystemOrder::FrameLimiter;
  }

  template <>
  SystemOrder GetSystemOrder<UWUTest::LockedFrameLimiterSys<120>>()
  {
    return SystemOrder::FrameLimiter;
  }

  template <>
  SystemOrder GetSystemOrder<UWUTest::LockedFrameLimiterSys<144>>()
  {
    return SystemOrder::FrameLimiter;
  }

  template <>
  SystemOrder GetSystemOrder<UWUTest::LockedFrameLimiterSys<240>>()
  {
    return SystemOrder::FrameLimiter;
  }
#pragma endregion

} // namespace UWUEngine
