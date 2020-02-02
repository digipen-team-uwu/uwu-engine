#pragma once

namespace UWUEngine
{

enum class SystemOrder
{
  FrameRate,
  StateMachine,
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

enum class ComponentOrder
{
  Animation,
  SpineAnimation,
  SpineSkeleton,
  Behavior,
  Physics,
  Collider,
};

template <typename E, class T> constexpr E GetOrder();

} // namespace UWUEngine
