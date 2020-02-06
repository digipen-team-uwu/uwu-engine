/******************************************************************************/
/*!
\par        Project Umbra
\file       SpotLight.h
\author     Chau Nguyen
\date       2019/11/20
\brief      Spot Light

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Graphics/Lighting/LightSys.h>

namespace UWUEngine
{

template<>
class LightSystem<LightType::SpotLight> : public LightBase
{
public:
  LightSystem();
  ~LightSystem() = default;
  void Update() override;

  void SetPosition(EntityID ID, const glm::vec3& pos);
  void SetDirection(EntityID ID, const glm::vec3& dir);

  void SetAmbient(EntityID ID, const glm::vec3& ambient);
  void SetDiffuse(EntityID ID, const glm::vec3& diffuse);
  void SetSpecular(EntityID ID, const glm::vec3& specular);

  void SetConstant(EntityID ID, float constant);
  void SetLinear(EntityID ID, float linear);
  void SetQuadratic(EntityID ID, float quadratic);

  void SetCutOff(EntityID ID, float cutoff);
  void SetOuterCutOff(EntityID ID, float outer_cutoff);

  const glm::vec3& GetPosition(EntityID ID);
  const glm::vec3& GetDirection(EntityID ID);

  const glm::vec3& GetAmbient(EntityID ID);
  const glm::vec3& GetDiffuse(EntityID ID);
  const glm::vec3& GetSpecular(EntityID ID);

  float GetConstant(EntityID ID);
  float GetLinear(EntityID ID);
  float GetQuadratic(EntityID ID);

  float GetCutOff(EntityID ID);
  float GetOuterCutOff(EntityID ID);

  std::vector<glm::vec3>& GetArrayPosition();
  std::vector<glm::vec3>& GetArrayDirection();

  std::vector<glm::vec3>& GetArrayAmbient();
  std::vector<glm::vec3>& GetArrayDiffuse();
  std::vector<glm::vec3>& GetArraySpecular();

  std::vector<float>& GetArrayConstant();
  std::vector<float>& GetArrayLinear();
  std::vector<float>& GetArrayQuadratic();

  std::vector<float>& GetArrayCutOff();
  std::vector<float>& GetArrayOuterCutOff();

private:
  EntityVector<glm::vec3> position_;
  EntityVector<glm::vec3> direction_;

  EntityVector<glm::vec3> ambient_;
  EntityVector<glm::vec3> diffuse_;
  EntityVector<glm::vec3> specular_;

  EntityVector<float> constant_;
  EntityVector<float> linear_;
  EntityVector<float> quadratic_;

  EntityVector<float> cutOff_;
  EntityVector<float> outerCutOff_;
};

}