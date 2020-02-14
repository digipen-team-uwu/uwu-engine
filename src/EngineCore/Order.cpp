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
SystemOrder GetSystemOrder<CompSpaceSys>()
{
  return SystemOrder::CompSpace;
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

template<>
SystemOrder GetSystemOrder<CameraSys>()
{
  return SystemOrder::Camera;
}

template<>
SystemOrder GetSystemOrder<PhysicsSys>()
{
  return SystemOrder::Physics;
}

#pragma endregion 

#pragma region Modules
template<>
SystemOrder GetSystemOrder<TextureLoaderMod>()
{
  return SystemOrder::TextureLoader;
}

template<>
SystemOrder GetSystemOrder<UBOMod>()
{
  return SystemOrder::UBOMod;
}
#pragma endregion 

template<>
SystemOrder GetSystemOrder<SpineDataMod>()
{
  return SystemOrder::SpineData;
}
template<>
SystemOrder GetSystemOrder<SSBOMod>()
{
  return SystemOrder::SSBOMod;
}

#pragma endregion 

#pragma region Components
#pragma region Component
template<>
ComponentOrder GetComponentOrder<EntityComp>()
{
  return ComponentOrder::Entity;
}

template<>
ComponentOrder GetComponentOrder<TransformComp>()
{
  return ComponentOrder::Transform;
}

template<>
ComponentOrder GetComponentOrder<PhysicsComp>()
{
  return ComponentOrder::Physics;
}

#pragma endregion 

} // namespace UWUEngine
