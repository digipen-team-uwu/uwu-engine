#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Space.h>
#include <UWUEngine/Component/AllComponents.h>

namespace UWUEngine
{

class CompSpaceSys : public System
{
public:
  using EnvironmentSpace  = Space<IComponent, EntityComp, TransformComp, TextureComp/*, AnimationComp*/>;
  using UISpace           = Space<IComponent, EntityComp, TransformComp, PhysicsComp, TextureComp/*, AnimationComp, BehaviorComp*/>;
  using ParticleSpace     = Space<IComponent, EntityComp, TransformComp, PhysicsComp/*, AnimationComp, BehaviorComp*/>;
  using GameplaySpace     = Space<IComponent, EntityComp, TransformComp, PhysicsComp, SpineAnimationComp, SpineSkeletonComp, ColliderComp>;
  using LightSpace        = Space<IComponent, EntityComp, TransformComp /*, LightingComp*/>;
  using DebugSpace        = Space<IComponent, EntityComp, TransformComp, TextureComp/*, BehaviorComp& */>;

  CompSpaceSys(ISpace* p) : System(p),
  space_environment(p),
  space_ui(p),
  space_particle(p),
  space_gameplay(p),
  space_light(p),
  space_debug(p)
  {}
  ~CompSpaceSys() {}
  void Update() override{}

  EnvironmentSpace space_environment;
  UISpace          space_ui;
  ParticleSpace    space_particle;
  GameplaySpace    space_gameplay;
  LightSpace       space_light;
  DebugSpace       space_debug;
};

}
