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

template<>
SystemOrder GetSystemOrder<InputSys>()
{
  return SystemOrder::Input;
}

template<>
SystemOrder GetSystemOrder<TimerSys>()
{
  return SystemOrder::Timer;
}

template<>
SystemOrder GetSystemOrder<SceneSys>()
{
  return SystemOrder::SceneManager;
}

} // namespace UWUEngine
