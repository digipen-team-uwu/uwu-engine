#pragma once
#include <UWUEngine/Component/BehaviorComp.h>
#include <UWUEngine/Component/EntityComp.h>

namespace UWUEngine
{
  template<>
  class Behavior<EntityComp::FALLS> : public BaseBehavior
  {
  public:
    Behavior(EntityID id, ISpace *space) : BaseBehavior(id, space) {}
    void Update() override;
  };
}