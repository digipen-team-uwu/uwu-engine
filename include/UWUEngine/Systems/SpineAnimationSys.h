#pragma once

#include <UWUEngine/System.h>

namespace UWUEngine
{
  //Forward Declaration
  class SpineAnimationComp;
  class SpineSkeletonComp;

  class SpineAnimationSys : public System
  {
  public:
    SpineAnimationSys(ISpace* p) : System(p){}

    ~SpineAnimationSys() override = default;
    void Update() override;

  private:
    void UpdateSpace(SpineAnimationComp& animComp, SpineSkeletonComp& skelComp);
  };
  
}
