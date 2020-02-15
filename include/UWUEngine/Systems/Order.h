#pragma once
#include <UWUEngine/System.h>
//#include <UWUEngine/Component/Component.h>

namespace UWUEngine
{
  class IComponent;
enum class SystemOrder : unsigned
{
  Invalid = -1,
  Event,
  Log,
  Input,
  FrameLimiter,
  SceneManager,
  Editor,
  Entity,
  Atlas,
  EntityVec,
  UI,
  HUD,
  Light,
  Debug,
  Timer,
  Camera,
  Render,
  Action,
  Physics,
  Collider,
  
  Window, // last one PWEASE

  //Modules, Order doesn't matter
  CompSpace,
  TextureLoader,
  TextureAtlaser,
  SpineData,
  UBOMod,
  SSBOMod,
};

  // order does not matter at all
enum class ComponentOrder : unsigned
{
  Entity,
  Transform,
  Animation,
  SpineAnimation,
  SpineSkeleton,
  Behavior,
  Physics,
  Collider,
  Texture,
};


template<class T>
SystemOrder GetSystemOrder();

template<class T>
constexpr ComponentOrder GetComponentOrder();


template <class T>
constexpr auto GetOrder() -> typename std::enable_if<std::is_base_of_v<System, T>, SystemOrder>::type
{
  return GetSystemOrder<T>();
}

template <class T>
constexpr auto GetOrder() -> typename std::enable_if<std::is_base_of_v<IComponent, T>, ComponentOrder>::type
{
  return GetComponentOrder<T>();
}

} // namespace UWUEngine
