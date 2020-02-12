/******************************************************************************/
/*!
\par        Project Umbra
\file       Lighting.h
\author     Chau Nguyen
\date       2019/11/7
\brief      Lighting

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Entity/EntityVector.h>
#include <UWUEngine/System.h>
#include <glm/glm.hpp>
#include <vector>

namespace UWUEngine
{

enum class LightType
{
  DirectionalLight,
  PointLight,
  SpotLight,

  Total
};

class LightBase
{
public:
  LightBase() = default;
  virtual ~LightBase() = default;
  virtual void Update() = 0;
  LightBase(const LightBase&) = default;
  LightBase& operator=(const LightBase&) = default;
  LightBase(LightBase&&) = default;
  LightBase& operator=(LightBase&&) = default;
};

//int RegisterSystemHelper<LightBase>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<LightBase>(SystemInitOrder::LAST, SystemUpdateOrder::LAST);

template<LightType T>
class LightSystem : public LightBase
{
public:
  LightSystem() = default;
  ~LightSystem() = default;
  void Update() override {};
  LightSystem(const LightSystem&) = default;
  LightSystem& operator=(const LightSystem&) = default;
  LightSystem(LightSystem&&) = delete;
  LightSystem& operator=(LightSystem&&) = default;
};

}

// specialization light type
#include <UWUEngine/Graphics/Lighting/DirectionalLight.h>
#include <UWUEngine/Graphics/Lighting/PointLight.h>
#include <UWUEngine/Graphics/Lighting/SpotLight.h>

namespace UWUEngine
{

class LightSys : public System
{
private:
  class LightData;
  class MaterialData;
public:
  LightSys(ISpace*);
  ~LightSys() = default;
  void Update() override;

  void Init();
  void Change();

  void Activate();
  void Deactivate();

  void SetLightAmbient(const glm::vec3& ambient);
  void SetLightDiffuse(const glm::vec3& diffuse);
  void SetLightSpecular(const glm::vec3& specular);
  void SetLightPosition(const glm::vec3& new_pos);
  void SetLightViewPosition(const glm::vec3& view_pos);
  void SetLightColor(const glm::vec3& new_color);

  const glm::vec3& GetLightAmbient() const;
  const glm::vec3& GetLightDiffuse() const;
  const glm::vec3& GetLightSpecular() const;
  const glm::vec3& GetLightPosition() const;
  const glm::vec3& GetLightViewPosition() const;
  const glm::vec3& GetLightColor() const;

  void SetMaterialAmbient(const glm::vec3& ambient);
  void SetMaterialDiffuse(const glm::vec3& diffuse);
  void SetMaterialSpecular(const glm::vec3& specular);
  void SetMaterialShininess(float shininess);

  const glm::vec3& GetMaterialAmbient() const;
  const glm::vec3& GetMaterialDiffuse() const;
  const glm::vec3& GetMaterialSpecular() const;
  const float GetMaterialShininess() const;

  void CreateSSBO(LightType light_type);
  void InitPointLight(GLuint amount = 3);

private:
  GLuint ssbo_plight_;
  GLuint ssbo_dlight_;
  GLuint ssbo_splight_;

  std::vector<LightSystem<LightType::PointLight>> PointLight_;
  std::vector<LightSystem<LightType::DirectionalLight>> DirLight_;
  std::vector<LightSystem<LightType::SpotLight>> SpotLight_;

  class LightData
  {
  public:
    glm::vec3 Pos_;
    glm::vec3 View_;
    glm::vec3 Ambient_;
    glm::vec3 Diffuse_;
    glm::vec3 Specular_;
    glm::vec3 Color_;
  };
  class MaterialData
  {
  public:
    glm::vec3 Ambient_;
    glm::vec3 Diffuse_;
    glm::vec3 Specular_;
    float Shininess_;
  };
  void LightToggle();
  LightData light_;
  MaterialData material_;
  bool lightOn_;
};

}