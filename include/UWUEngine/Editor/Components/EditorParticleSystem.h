#pragma once
#include <UWUEngine/Editor/EditorComponent.h>
#include <UWUEngine/Helper.h>
#include<glm/glm.hpp>
namespace Editors
{
  class ParticleEmitter final : public Component
  {
  public:
    ParticleEmitter(const std::string& name);
    ~ParticleEmitter() override = default;

  protected:
    void CheckActive(EntityID id) override;
    void UpdateUI() override;
    void UpdateComponent(EntityID id) override;

  private:
    Element<FlatOrRange<glm::vec4>> color{"Color"};
    Element<FlatOrRange<glm::vec4>> endColor{"End Color"};
    Element<FlatOrRange<float>> colorRate{"Color Change Rate"};
    Element<FlatOrRange<glm::vec3>> scale{ "Scale" };
    Element<FlatOrRange<glm::vec3>> endScale{ "End Scale" };
    Element<FlatOrRange<float>> scaleRate{ "Scale Change Rate" };
  };
}