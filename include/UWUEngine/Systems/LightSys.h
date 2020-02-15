#pragma once

#include <UWUEngine/System.h>
#include <glm/gtx/transform.hpp>

namespace UWUEngine
{
  class LightSys : public System
  {
  public:
    LightSys(ISpace* space);
    ~LightSys() override = default;
    void Update() override;

    void LightToggle();

#pragma region Setter
    void SetLightAmbient(const glm::vec3& ambient);
    void SetLightDiffuse(const glm::vec3& diffuse);
    void SetLightSpecular(const glm::vec3& specular);
    void SetLightPosition(const glm::vec3& new_pos);
    void SetLightViewPosition(const glm::vec3& view_pos);
    void SetLightColor(const glm::vec3& new_color);
#pragma endregion

#pragma region Getter
    const glm::vec3& GetLightAmbient() const;
    const glm::vec3& GetLightDiffuse() const;
    const glm::vec3& GetLightSpecular() const;
    const glm::vec3& GetLightPosition() const;
    const glm::vec3& GetLightViewPosition() const;
    const glm::vec3& GetLightColor() const;
#pragma endregion 

  private:
    glm::vec3 Pos_;
    glm::vec3 View_;
    glm::vec3 Ambient_;
    glm::vec3 Diffuse_;
    glm::vec3 Specular_;
    glm::vec3 Color_;
    bool lightOn_;
  };
}