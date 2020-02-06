/******************************************************************************/
/*!
\par        Project Umbra
\file       DirectionalLight.h
\author     Chau Nguyen
\date       2019/11/20
\brief      Directional Light

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Graphics/Lighting/LightSys.h>

namespace UWUEngine
{

template<>
class LightSystem<LightType::DirectionalLight> : public LightBase
{
public:
  LightSystem();
  ~LightSystem() = default;
  void Update() override;

  LightSystem(const LightSystem<LightType::DirectionalLight>&) = default;
  LightSystem<LightType::DirectionalLight>& operator=(const LightSystem<LightType::DirectionalLight>&) = default;
  LightSystem(LightSystem<LightType::DirectionalLight>&&) = default;
  LightSystem<LightType::DirectionalLight>& operator=(LightSystem<LightType::DirectionalLight>&&) = default;

  void SetDirection(const glm::vec3& dir);
  void SetAmbient(const glm::vec3& ambient);
  void SetDiffuse(const glm::vec3& diffuse);
  void SetSpecular(const glm::vec3& specular);

  const glm::vec3& GetDirection() const;
  const glm::vec3& GetAmbient() const;
  const glm::vec3& GetDiffuse() const;
  const glm::vec3& GetSpecular() const;

private:
  glm::vec3 direction_;
  glm::vec3 ambient_;
  glm::vec3 diffuse_;
  glm::vec3 specular_;
};

}
