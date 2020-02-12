#include <UWUEngine/Order.h>

#pragma region system_includes
#include <UWUEngine/WindowSys.h>
#include <UWUEngine/Timer.h>
#include <UWUEngine/AllSystems.h>
#pragma endregion 

namespace UWUEngine
{

template<>
constexpr SystemOrder GetSystemOrder<WindowSys>()
{
  return SystemOrder::Window;
}

template<>
constexpr SystemOrder GetSystemOrder<FrameLimiterSys>()
{
  return SystemOrder::FrameRate;
}

template<>
constexpr SystemOrder GetSystemOrder<TimerSys>()
{
  return SystemOrder::Timer;
}



} // namespace UWUEngine