#include <UWUEngine/Systems/Order.h>

#pragma region system_includes
#include <UWUEngine/Systems/AllSystems.h>
#include <UWUEngine/Component/AllComponents.h>
#pragma endregion 

namespace UWUEngine
{
#pragma region Systems
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
SystemOrder GetSystemOrder<EntitySys>()
{
  return SystemOrder::Entity;
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

template<>
SystemOrder GetSystemOrder<RenderSys>()
{
  return SystemOrder::Render;
}
#pragma endregion 


#pragma region Modules
template<>
SystemOrder GetSystemOrder<TextureLoaderMod>()
{
  return SystemOrder::TextureLoader;
}



#pragma endregion 

template<>
ComponentOrder GetComponentOrder<EntityComp>()
{
  return ComponentOrder::Entity;
}

} // namespace UWUEngine
