#include <UWUEngine/Component/LightComp.h>

using namespace UWUEngine;

LightComp::LightComp(ISpace* space) : Component<LightComp, Light>(space)
{ 
}

void Light::SetShininess(const float& shininess)
{
  shininess_ = shininess;
}

const float& Light::GetShininess() const
{
  return shininess_;
}

Light LightComp::operator[](EntityID ID)
{
  return Light(shininess_[ID]);
}

void LightComp::SetShininess(EntityID ID, const float shininess)
{
  Light light = this->operator[](ID);
  light.SetShininess(shininess);
}

float LightComp::GetShininess(EntityID ID)
{
  Light light = this->operator[](ID);
  return light.GetShininess();
}

const std::vector<float>& LightComp::GetArrayShininess()
{
  return shininess_;
}