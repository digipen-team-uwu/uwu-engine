/******************************************************************************/
/*!
\par        Project Umbra
\file       Lighting.h
\author     Chau Nguyen
\date       2019/11/7
\brief      Lighting

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Graphics/Lighting/LightSys.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Graphics/CameraSys.h>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Input/InputSys.h>
#include <UWUEngine/Graphics/Shader/UBOModule.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <glm/gtc/type_ptr.hpp>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Component/LightingComponentManager.h>

namespace UWUEngine
{

LightSys::LightSys(ISpace* p) : System(p)
{
  Init();
  InitPointLight(1);
  CreateSSBO(LightType::PointLight);
}


void LightSys::CreateSSBO(LightType light_type)
{
  if (light_type == LightType::PointLight)
  {
    glCreateBuffers(1, &ssbo_plight_);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo_plight_);
    glNamedBufferStorage(ssbo_plight_, sizeof(LightSystem<LightType::PointLight>) * PointLight_.size(),
                         nullptr, GL_DYNAMIC_STORAGE_BIT);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 5);
    //glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 5, ssbo_plight_, 0,
    //    sizeof(LightSystem<LightType::PointLight>) * PointLight_.size());


    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, ssbo_plight_);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // sending data to ssbo
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo_plight_);
    for (int i = 0; i < PointLight_.size(); ++i)
    {
      //TraceLogger:: << "size: " << sizeof(LightSystem<LightType::PointLight>) << std::endl;
      glNamedBufferSubData(ssbo_plight_, 0,
                           sizeof(glm::vec3), glm::value_ptr(PointLight_[i].GetPosition()));
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 5);
  }

}

void LightSys::InitPointLight(GLuint amount)
{
  for (int i = 0; i < amount; ++i)
  {
    LightSystem<LightType::PointLight> plight({ 1000.0f + i * 2500.f, 5000.0f, 500.f }, { 0.05f,0.05f,0.05f },
                                              { 0.8f,0.8f,0.8f }, { 1.0f,1.0f,1.0f }, 1.0f, 0.09f, 0.032f);
    PointLight_.push_back(plight);
  }
}

void LightSys::Init()
{
  light_.Color_ = glm::vec3(0.2f, 0.2f, 0.3f);
  light_.Diffuse_ = light_.Color_ * glm::vec3(0.5f); //.5
  light_.Ambient_ = light_.Diffuse_ * glm::vec3(0.2f); //.2
  light_.Specular_ = glm::vec3(1.f);
  light_.Pos_ = glm::vec3(308.0f, 5634.0f, 0.0f);
  light_.View_ = Get<CameraSys>().GetPosition();

  //material_.Ambient_ = glm::vec3(1.0f, 0.5f, 0.5f);
  //material_.Diffuse_ = glm::vec3(1.0f, 0.5f, 0.5f);
  //material_.Specular_ = glm::vec3(1.0f, 1.0f, 1.0f);
  //material_.Shininess_ = 256.0f;

  lightOn_ = true;
}

void LightSys::Change()
{
  light_.Color_.x = static_cast<float>(glm::clamp(sin(glfwGetTime() * 1.2f), 0.3, 1.0));
  light_.Color_.y = static_cast<float>(glm::clamp(cos(glfwGetTime() * 0.5f), 0.3, 1.0));
  light_.Color_.z = static_cast<float>(glm::clamp(sin(glfwGetTime() * 0.2f), 0.3, 1.0));

  light_.Diffuse_ = light_.Color_ * glm::vec3(1.f); //.95f
  light_.Ambient_ = light_.Diffuse_ * glm::vec3(0.9f); //.7f
}

void LightSys::Activate()
{
  lightOn_ = true;
}

void LightSys::Deactivate()
{
  lightOn_ = false;
}

void LightSys::Update()
{
  auto playerID = PlayerData::GetPlayerID();

  auto& player_pos = TransformComponentManager::GetTranslation(playerID);

  light_.Pos_.x = player_pos.x;
  light_.Pos_.y = player_pos.y;
  light_.Pos_.z = 5000.0f;
  light_.Ambient_ = glm::vec3(0.1f, 0.1f, 0.2f);
  light_.View_ = Get<CameraSys>().GetPosition();

  LightToggle();
  //std::cout << "light pos x: " << light_.Pos_.x << " light pos y: " << light_.Pos_.y << std::endl;
  //std::cout << "player pos x: " << player_pos.x << " player pos y: " << player_pos.y << std::endl;

  const GLSLShader& shader = Get<ShaderModule>().GetEntityShader();
  shader.Use();
  Get<UBOModule>().ShootDataToUBO(UBOModule::Light);
  shader.SetUniform("lightOn", lightOn_);
  shader.UnUse();

  //float dt = FrameRateController::GetDeltaTime<float>();
  //light_.Pos_.z += 800.f * dt * (float)(!!InputManager::KeyHeld('u') - !!InputManager::KeyHeld('j'));
  //TraceLogger::Log(TraceLogger::TRACE) << light_.Pos_.z << std::endl;
  //light_.Pos_.x -= 800.f * dt * (float)(!!InputManager::KeyHeld('h') - !!InputManager::KeyHeld('k'));

  //auto ambient = LightSys::GetLightAmbient();
  //ambient += 0.05f * (float)(!!InputManager::KeyHeld('m') - !!InputManager::KeyHeld('n'));
  //LightSys::SetLightAmbient(ambient);
  //std::cout << "ambient x: " << ambient.x << " ambient y: " << ambient.y << 
  //    "ambient z " << ambient.z << std::endl;
  //
  //
  //auto specular = LightSys::GetLightSpecular();
  //specular += 0.05f * (float)(!!InputManager::KeyHeld('z') - !!InputManager::KeyHeld('c'));
  //LightSys::SetLightSpecular(specular);

  //TODO::Serialized shininess
  if (!lightOn_)
  {
    return;
  }
  for (auto& i : EntityManager::GetIDs())
  {
    if (EntityManager::GetType(i) != EntityManager::Dropped)
    {
      LightingComp::SetShininess(i, 16.0f);
    }
  }
}

void LightSys::LightToggle()
{
  if (Get<InputSys>().KeyPressed('o'))
  {
    if (lightOn_)
    {
      lightOn_ = false;
    }
    else
    {
      lightOn_ = true;
    }
  }
}

void LightSys::SetLightAmbient(const glm::vec3& ambient)
{
  light_.Ambient_ = ambient;
}

void LightSys::SetLightDiffuse(const glm::vec3& diffuse)
{
  light_.Diffuse_ = diffuse;
}

void LightSys::SetLightSpecular(const glm::vec3& specular)
{
  light_.Specular_ = specular;
}

void LightSys::SetLightPosition(const glm::vec3& new_pos)
{
  light_.Pos_ = new_pos;
}

void LightSys::SetLightViewPosition(const glm::vec3& view_pos)
{
  light_.View_ = view_pos;
}

void LightSys::SetLightColor(const glm::vec3& new_color)
{
  light_.Color_ = new_color;
}

const glm::vec3& LightSys::GetLightAmbient() const
{
  return light_.Ambient_;
}

const glm::vec3& LightSys::GetLightDiffuse() const
{
  return light_.Diffuse_;
}

const glm::vec3& LightSys::GetLightSpecular() const
{
  return light_.Specular_;
}

const glm::vec3& LightSys::GetLightPosition() const
{
  return light_.Pos_;
}

const glm::vec3& LightSys::GetLightViewPosition() const
{
  return light_.View_;
}

const glm::vec3& LightSys::GetLightColor() const
{
  return light_.Color_;
}

void LightSys::SetMaterialAmbient(const glm::vec3& ambient)
{
  material_.Ambient_ = ambient;
}

void LightSys::SetMaterialDiffuse(const glm::vec3& diffuse)
{
  material_.Diffuse_ = diffuse;
}

void LightSys::SetMaterialSpecular(const glm::vec3& specular)
{
  material_.Specular_ = specular;
}

void LightSys::SetMaterialShininess(float shininess)
{
  material_.Shininess_ = shininess;
}

const glm::vec3& LightSys::GetMaterialAmbient() const
{
  return material_.Ambient_;
}

const glm::vec3& LightSys::GetMaterialDiffuse() const
{
  return material_.Diffuse_;
}

const glm::vec3& LightSys::GetMaterialSpecular() const
{
  return material_.Specular_;
}

const float LightSys::GetMaterialShininess() const
{
  return material_.Shininess_;
}

}
