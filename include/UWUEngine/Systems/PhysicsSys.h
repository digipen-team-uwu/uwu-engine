#pragma once

#include <UWUEngine/System.h>

namespace UWUEngine
{
  // Forward declaration
  class TransformComp;
  class PhysicsComp;
  class EntityComp;

  class PhysicsSys final : public System
  {
  public:
    PhysicsSys(ISpace* p);
    ~PhysicsSys() override = default;
    void Update() override;

  private:
    void UpdateSpace(EntityComp& entityComp, TransformComp& transformComp, PhysicsComp& physicsComp);
  };
}
