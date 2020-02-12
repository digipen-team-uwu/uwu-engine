#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Space.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Component/BehaviorComp.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <UWUEngine/Component/LightingComponentManager.h>

namespace UWUEngine
{

class CompSpaceSys : System
{
public:

  using EnvironmentSpace  = Space<IComponent, TransformComp, TextureComp, AnimationComp>;
  using UISpace           = Space<IComponent, TransformComp, TextureComp, AnimationComp, PhysicsComp, BehaviorComp>;
  using ParticleSpace     = Space<IComponent, TransformComp, TextureComp, AnimationComp, PhysicsComp, BehaviorComp>;
  using GameplaySpace     = Space<IComponent, TransformComp, PhysicsComp, SpineAnimationComp, SpineSkeletonComp, ColliderComp>;
  using LightSpace        = Space<IComponent, TransformComp, LightingComp>;
  using DebugSpace        = Space<IComponent, TransformComp, TextureComp, BehaviorComp>;

  CompSpaceSys(ISpace*);
  ~CompSpaceSys();

  EnvironmentSpace space_environment;
  UISpace          space_ui;
  ParticleSpace    space_particle;
  GameplaySpace    space_gameplay;
  LightSpace       space_light;
  DebugSpace       space_debug;
};

}
