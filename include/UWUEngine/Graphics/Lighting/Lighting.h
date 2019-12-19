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
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityVector.h>
#include <UWUEngine/BaseSystem.h>
#include <glm/glm.hpp>
#include <vector>

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

// specialization light type
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Lighting : public BaseSystem<Lighting>
{
private:
  class LightData;
  class MaterialData;
public:
    Lighting();
    ~Lighting() = default;
    void Update() override;

    static void Init();
    static void Change();

  static void Activate();
  static void Deactivate();

    static void SetLightAmbient(const glm::vec3& ambient);
    static void SetLightDiffuse(const glm::vec3& diffuse);
    static void SetLightSpecular(const glm::vec3& specular);
    static void SetLightPosition(const glm::vec3& new_pos);
    static void SetLightViewPosition(const glm::vec3& view_pos);
    static void SetLightColor(const glm::vec3& new_color);

    static const glm::vec3& GetLightAmbient();
    static const glm::vec3& GetLightDiffuse();
    static const glm::vec3& GetLightSpecular();
    static const glm::vec3& GetLightPosition();
    static const glm::vec3& GetLightViewPosition();
    static const glm::vec3& GetLightColor();

    static void SetMaterialAmbient(const glm::vec3& ambient);
    static void SetMaterialDiffuse(const glm::vec3& diffuse);
    static void SetMaterialSpecular(const glm::vec3& specular);
    static void SetMaterialShininess(float shininess);

    static const glm::vec3& GetMaterialAmbient();
    static const glm::vec3& GetMaterialDiffuse();
    static const glm::vec3& GetMaterialSpecular();
    static const float GetMaterialShininess();

    static void CreateSSBO(LightType light_type);
    static void InitPointLight(GLuint amount = 3);

private:
    static GLuint ssbo_plight_;
    static GLuint ssbo_dlight_;
    static GLuint ssbo_splight_;

    static std::vector<LightSystem<LightType::PointLight>> PointLight_;
    static std::vector<LightSystem<LightType::DirectionalLight>> DirLight_;
    static std::vector<LightSystem<LightType::SpotLight>> SpotLight_;

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
    static void LightToggle();
    static LightData light_;
    static MaterialData material_;
    static bool lightOn_;
};
