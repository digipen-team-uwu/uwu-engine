#include <UWUEngine/Systems/Order.h>

#pragma region system_includes
#include <UWUEngine/Systems/AllSystems.h>
#pragma endregion 

namespace UWUEngine
{

template<>
SystemOrder GetSystemOrder<WindowSys>()
{
  return SystemOrder::Window;
}

template<>
SystemOrder GetSystemOrder<FrameLimiterSys>()
{
  return SystemOrder::FrameLimiter;
}

template<>
SystemOrder GetSystemOrder<LogSys>()
{
  return SystemOrder::Log;
}

template<>
SystemOrder GetSystemOrder<EventSys>()
{
  return SystemOrder::Event;
}

} // namespace UWUEngine
