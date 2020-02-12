#pragma once
#include <UWUEngine/constants.h>
#include <UWUEngine/Graphics/Lighting/LightSys.h>
#include <UWUEngine/Component/Component.h>
#include <vector>

namespace LC = LightingConstant;

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

  class LightingComp : public Component<LightingComp, Light>
  {
  public:
    LightingComp() = default;
    ~LightingComp() = default;
    void Update() override;
    void InitObject(EntityID ID) override {};
    void ShutdownObject(EntityID ID) override {};

    Light operator[](EntityID ID);

    // Material
    void SetShininess(EntityID ID, const float shininess);
    float GetShininess(EntityID ID);
    const std::vector<float>& GetArrayShininess();

  private:

    // TODO: instancing those vectors below in the future
    //EntityVector<LightType> lightTypes;

    // Material
    std::vector<float> shininess_;
  };
}
