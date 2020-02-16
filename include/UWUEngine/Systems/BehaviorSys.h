#pragma once
#include <UWUEngine/System.h>

namespace UWUEngine
{
  class BehaviorSys : public System
  {
  public:
    BehaviorSys(ISpace* p) : System(p){}
    ~BehaviorSys() override = default;
    void Update() override;
  private:
    void UpdateBehaviors(ISpace *space);
  };
}