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

namespace UWUEngine
{

class CompSpaceSys : System
{
public:

  using EnvironmentSpace  = Space<IComponent, TransformComp, TextureComp, AnimationComp>;
  using UISpace           = Space<IComponent, TransformComp, TextureComp, AnimationComp, PhysicsComp, BehaviorComp>;
  using ParticleSpace     = Space<IComponent, TransformComp, TextureComp, AnimationComp, PhysicsComp, BehaviorComp>;
  using GameplaySpace     = Space<IComponent, TransformComp, PhysicsComp, SpineAnimationComp, SpineSkeletonComp, ColliderComp>;


  CompSpaceSys(ISpace*);
  ~CompSpaceSys();

  EnvironmentSpace environment_space;
};

}
