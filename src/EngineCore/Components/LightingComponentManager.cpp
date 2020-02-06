#include <UWUEngine/Component/LightingComponentManager.h>

namespace UWUEngine
{
  void Light::SetShininess(const float& shininess)
  {
    shininess_ = shininess;
  }

  const float& Light::GetShininess() const
  {
    return shininess_;
  }

  void LightingComp::Update()
  {
  }

  Light LightingComp::operator[](EntityID ID)
  {
    return Light(shininess_[ID]);
  }

  void LightingComp::SetShininess(EntityID ID, const float shininess)
  {
    Light light = this->operator[](ID);
    light.SetShininess(shininess);
  }

  float LightingComp::GetShininess(EntityID ID)
  {
    Light light = this->operator[](ID);
    return light.GetShininess();
  }

  const std::vector<float>& LightingComp::GetArrayShininess()
  {
    return shininess_;
  }
}
