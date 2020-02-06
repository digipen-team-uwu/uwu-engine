/******************************************************************************/
/*!
\par        Project Umbra
\file       PointLight.h
\author     Chau Nguyen
\date       2019/11/20
\brief      Point Light

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Graphics/Lighting/LightSys.h>

namespace UWUEngine
{

template<>
class LightSystem<LightType::PointLight> : public LightBase
{
public:
  LightSystem() = default;
  LightSystem(const glm::vec3 pos, const glm::vec3 ambient, const glm::vec3 diffuse,
              const glm::vec3 specular, const float constant, const float linear, const float quadratic)
    : position_(pos), ambient_(ambient), diffuse_(diffuse), specular_(specular), constant_(constant),
    linear_(linear), quadratic_(quadratic)
  {}
  ~LightSystem() = default;

  LightSystem(const LightSystem<LightType::PointLight>&) = default;
  LightSystem<LightType::PointLight>& operator=(const LightSystem<LightType::PointLight>&) = default;
  LightSystem(LightSystem<LightType::PointLight>&&) = default;
  LightSystem<LightType::PointLight>& operator=(LightSystem<LightType::PointLight>&&) = default;

  void Update() override;

  void SetPosition(const glm::vec3& pos);
  void SetAmbient(const glm::vec3& ambient);
  void SetDiffuse(const glm::vec3& diffuse);
  void SetSpecular(const glm::vec3& specular);

  void SetConstant(const float constant);
  void SetLinear(const float linear);
  void SetQuadratic(const float quadratic);

  const glm::vec3& GetPosition() const;
  const glm::vec3& GetAmbient() const;
  const glm::vec3& GetDiffuse() const;
  const glm::vec3& GetSpecular() const;

  float GetConstant() const;
  float GetLinear() const;
  float GetQuadratic() const;

private:
  glm::vec3 position_;
  glm::vec3 ambient_;
  glm::vec3 diffuse_;
  glm::vec3 specular_;
  float constant_;
  float linear_;
  float quadratic_;
};

}