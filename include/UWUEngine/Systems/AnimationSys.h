#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Component/TextureComp.h>
#include <glm/glm.hpp>

namespace UWUEngine
{
  using EntityID = unsigned;
  class AnimationSys : public System
  {
  public:
    AnimationSys(ISpace *space) : System(space){}
    static glm::vec2 indexToUvs(ISpace* space, EntityID id, int index);
    static glm::vec2 indexToUvs(TextureComp* texComp, EntityID id, int index);
    void Update() override;
  private:
    void UpdateAnimations(ISpace* space);
  };
}
