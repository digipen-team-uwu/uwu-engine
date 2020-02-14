#pragma once
#include <UWUEngine/System.h>

namespace UWUEngine
{
  class RenderSys : public System
  {
  public:
    RenderSys(ISpace*);
    ~RenderSys() = default;
    void Update() override;
    //static void DrawObject(EntityID ID);

  private:

    // data member to represent geometric model to be rendered
    // C++ requires this object to have a definition in render.cpp!!!
  };

}
