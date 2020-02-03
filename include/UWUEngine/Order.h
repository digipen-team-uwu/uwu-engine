#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Component/Component.h>

namespace UWUEngine
{

enum class SystemOrder : unsigned
{
  FrameRate,
  StateMachine,
  SceneManager,
  Editor,
  Entity,
  TexLoad,
  Atlas,
  EntityVec,
  UI,
  HUD,
  Light,
  Debug,
  Timer,
  Camera,
  Event,
  Render,
  Action,
  Input,
  Window,
};

enum class ComponentOrder : unsigned
{
  Animation,
  SpineAnimation,
  SpineSkeleton,
  Behavior,
  Physics,
  Collider,
};

// ReSharper disable CppFunctionIsNotImplemented
template<class T>
constexpr SystemOrder GetSystemOrder();

template<class T>
constexpr ComponentOrder GetComponentOrder();
// ReSharper restore CppFunctionIsNotImplemented

template <class T>
constexpr auto GetOrder() -> typename std::enable_if<std::is_base_of_v<System, T>, SystemOrder>::type
{
  return GetSystemOrder<T>();
}

template <class T>
constexpr auto GetOrder() -> typename std::enable_if<std::is_base_of_v<Component, T>, ComponentOrder>::type
{
  return GetComponentOrder<T>();
}

} // namespace UWUEngine
