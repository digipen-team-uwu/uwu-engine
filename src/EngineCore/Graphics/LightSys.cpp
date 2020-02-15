#include <UWUEngine/Systems/LightSys.h>
#include <UWUEngine/Modules/ShaderMod.h>
#include <UWUEngine/Modules/UBOMod.h>
#include <UWUEngine/Systems/InputSys.h>
#include <UWUEngine/Systems/CameraSys.h>
#include <UWUEngine/Component/LightComp.h>
#include <UWUEngine/Systems/CompSpaceSys.h>

using namespace UWUEngine;

LightSys::LightSys(ISpace* space) : System(space)
{
  Color_ = glm::vec3(0.2f, 0.2f, 0.3f);
  Diffuse_ = Color_ * glm::vec3(0.5f); //.5
  Ambient_ = Diffuse_ * glm::vec3(0.2f); //.2
  Specular_ = glm::vec3(1.f);
  Pos_ = Get<CameraSys>().GetCameraPosition();
  View_ = Get<CameraSys>().GetCameraPosition();
  lightOn_ = true;
}

void LightSys::Update()
{
  Ambient_ = glm::vec3(0.1f, 0.1f, 0.2f);
  Pos_ = Get<CameraSys>().GetCameraPosition();
  View_ = Get<CameraSys>().GetCameraPosition();
  LightToggle();
  auto& ubo = Get<UBOMod>();
  auto& shader = Get<ShaderMod>().GetEntityShader();
  shader.Use();
  ubo.ShootDataToUniformBuffer(ubo.Light);
  shader.SetUniform("lightOn", lightOn_);
  shader.UnUse();

  auto& entity = Get<CompSpaceSys>().space_light.Get<EntityComp>().GetIDs();
  for (int i = 0; i < entity.size(); ++i)
  {
    Get<LightComp>().SetShininess(i, 16.0f);
  }
}

void LightSys::LightToggle()
{
  if (Get<InputSys>().KeyPressed('o'))
  {
    lightOn_ = !lightOn_;
  }
}

#pragma region Setter
void LightSys::SetLightAmbient(const glm::vec3& ambient)
{
  Ambient_ = ambient;
}

void LightSys::SetLightDiffuse(const glm::vec3& diffuse)
{
  Diffuse_ = diffuse;
}

void LightSys::SetLightSpecular(const glm::vec3& specular)
{
  Specular_ = specular;
}

void LightSys::SetLightPosition(const glm::vec3& new_pos)
{
  Pos_ = new_pos;
}

void LightSys::SetLightViewPosition(const glm::vec3& view_pos)
{
  View_ = view_pos;
}

void LightSys::SetLightColor(const glm::vec3& new_color)
{
  Color_ = new_color;
}
#pragma endregion

#pragma region Getter
const glm::vec3& LightSys::GetLightAmbient() const
{
  return Ambient_;
}

const glm::vec3& LightSys::GetLightDiffuse() const
{
  return Diffuse_;
}

const glm::vec3& LightSys::GetLightSpecular() const
{
  return Specular_;
}

const glm::vec3& LightSys::GetLightPosition() const
{
  return Pos_;
}

const glm::vec3& LightSys::GetLightViewPosition() const
{
  return View_;
}

const glm::vec3& LightSys::GetLightColor() const
{
  return Color_;
}
#pragma endregion 
