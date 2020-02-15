#pragma once
#include <UWUEngine/System.h>

namespace UWUEngine
{
  //Forward Declaration
  class EntityComp;
  class SpineSkeletonComp;

  class RenderSys : public System
  {
  public:
    RenderSys(ISpace*);
    ~RenderSys();
    void Update() override;

  private:
    static void RenderSpine(SpineSkeletonComp&);
  };

}
