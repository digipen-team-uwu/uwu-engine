#pragma once

#include "UWUEngine/Component/Component.h"
#include "UWUEngine/Component/EntityComp.h"

namespace UWUEngine
{
  class Light
  {
  public:
    Light(float& shininess) : shininess_(shininess) {}
    void SetShininess(const float& shininess);
    const float& GetShininess() const;
  private:
    float& shininess_;
  };

  class LightComp : public Component<LightComp, Light>
  {
  public:
    LightComp(ISpace* space);
    void InitObject(EntityID ID) override {}
    void ShutdownObject(EntityID ID) override {}
    ~LightComp() override = default;

    Light operator[](EntityID ID);

    void SetShininess(EntityID ID, const float shininess);
    float GetShininess(EntityID ID);

    const std::vector<float>& GetArrayShininess();

  private:
    EntityVector<float> shininess_ = { parent };
  };
}