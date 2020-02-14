#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Space.h>
#include <UWUEngine/Component/TransformComp.h>

namespace UWUEngine
{

class CompSpaceSys : public System
{
public:
  using EnvironmentSpace  = Space<IComponent, EntityComp, TransformComp /*, TextureComp, AnimationComp*/>;
  using UISpace           = Space<IComponent, EntityComp, TransformComp /*, TextureComp, AnimationComp, PhysicsComp, BehaviorComp*/>;
  using ParticleSpace     = Space<IComponent, EntityComp, TransformComp /*, TextureComp, AnimationComp, PhysicsComp, BehaviorComp*/>;
  using GameplaySpace     = Space<IComponent, EntityComp, TransformComp /*, PhysicsComp , SpineAnimationComp, SpineSkeletonComp, ColliderComp*/>;
  using LightSpace        = Space<IComponent, EntityComp, TransformComp /*, LightingComp*/>;
  using DebugSpace        = Space<IComponent, EntityComp, TransformComp /*, TextureComp, BehaviorComp& */>;

  CompSpaceSys(ISpace* p) : System(p) {}
  ~CompSpaceSys() {};

  EnvironmentSpace space_environment;
  UISpace          space_ui;
  ParticleSpace    space_particle;
  GameplaySpace    space_gameplay;
  LightSpace       space_light;
  DebugSpace       space_debug;
};

}
