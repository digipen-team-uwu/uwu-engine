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
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/FrameRateController.h>
#include <iostream>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <glm/gtc/type_ptr.hpp>
#include <UWUEngine/Component/LightingComponentManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/GamePlay/PlayerController.h>

template<>
int RegisterSystemHelper<Lighting>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Lighting>(SystemInitOrder::Light, SystemUpdateOrder::Light);

Lighting::LightData Lighting::light_;
Lighting::MaterialData Lighting::material_;
bool Lighting::lightOn_;
std::vector<LightSystem<LightType::DirectionalLight>> Lighting::DirLight_ {goc::INITIAL_OBJECT_COUNT};
std::vector<LightSystem<LightType::PointLight>> Lighting::PointLight_{ goc::INITIAL_OBJECT_COUNT };
std::vector<LightSystem<LightType::SpotLight>> Lighting::SpotLight_{ goc::INITIAL_OBJECT_COUNT };

GLuint Lighting::ssbo_plight_;
GLuint Lighting::ssbo_dlight_;
GLuint Lighting::ssbo_splight_;

Lighting::Lighting()
{
    Init();
    InitPointLight(1);
    CreateSSBO(LightType::PointLight);
}


void Lighting::CreateSSBO(LightType light_type)
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

void Lighting::InitPointLight(GLuint amount)
{
    for (int i = 0; i < amount; ++i)
    {
        LightSystem<LightType::PointLight> plight({ 1000.0f + i * 2500.f, 5000.0f, 500.f }, { 0.05f,0.05f,0.05f },
            { 0.8f,0.8f,0.8f }, { 1.0f,1.0f,1.0f }, 1.0f, 0.09f, 0.032f);
        PointLight_.push_back(plight);
    }
}

void Lighting::Init()
{
    light_.Color_ = glm::vec3(0.2f, 0.2f, 0.3f);
    light_.Diffuse_ = light_.Color_ * glm::vec3(0.5f); //.5
    light_.Ambient_ = light_.Diffuse_ * glm::vec3(0.2f); //.2
    light_.Specular_ = glm::vec3(1.f);
    light_.Pos_ = glm::vec3(308.0f, 5634.0f, 0.0f);
    light_.View_ = Camera::GetCameraPosition();

    //material_.Ambient_ = glm::vec3(1.0f, 0.5f, 0.5f);
    //material_.Diffuse_ = glm::vec3(1.0f, 0.5f, 0.5f);
    //material_.Specular_ = glm::vec3(1.0f, 1.0f, 1.0f);
    //material_.Shininess_ = 256.0f;

    lightOn_ = true;
}

void Lighting::Change()
{
    light_.Color_.x = static_cast<float>(glm::clamp(sin(glfwGetTime() * 1.2f), 0.3, 1.0));
    light_.Color_.y = static_cast<float>(glm::clamp(cos(glfwGetTime() * 0.5f), 0.3,1.0));
    light_.Color_.z = static_cast<float>(glm::clamp(sin(glfwGetTime() * 0.2f), 0.3, 1.0));

    light_.Diffuse_ = light_.Color_ * glm::vec3(1.f); //.95f
    light_.Ambient_ = light_.Diffuse_ * glm::vec3(0.9f); //.7f
}

void Lighting::Activate()
{
  lightOn_ = true;
}

void Lighting::Deactivate()
{
  lightOn_ = false;
}

void Lighting::Update()
{
    auto playerID = PlayerData::GetPlayerID();

    auto& player_pos = TransformComponentManager::GetTranslation(playerID);

    light_.Pos_.x = player_pos.x;
    light_.Pos_.y = player_pos.y;
    light_.Pos_.z = 5000.f;
    light_.Ambient_ = glm::vec3(0.82, 0.82, 0.83);
    light_.View_ = light_.Pos_;

    LightToggle();
    //std::cout << "light pos x: " << light_.Pos_.x << " light pos y: " << light_.Pos_.y << std::endl;
    //std::cout << "player pos x: " << player_pos.x << " player pos y: " << player_pos.y << std::endl;

    const GLSLShader& shader = ShaderModule::GetEntityShader();
    shader.Use();
    UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::Light);
    //UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::Material);
    shader.SetUniform("lightOn", lightOn_);
    shader.UnUse();
    
    //float dt = FrameRateController::GetDeltaTime<float>();
    //light_.Pos_.y += 800.f * dt * (float)(!!InputManager::KeyHeld('u') - !!InputManager::KeyHeld('j'));
    //light_.Pos_.x -= 800.f * dt * (float)(!!InputManager::KeyHeld('h') - !!InputManager::KeyHeld('k'));

    //auto ambient = Lighting::GetLightAmbient();
    //ambient += 0.05f * (float)(!!InputManager::KeyHeld('m') - !!InputManager::KeyHeld('n'));
    //Lighting::SetLightAmbient(ambient);
    //std::cout << "ambient x: " << ambient.x << " ambient y: " << ambient.y << 
    //    "ambient z " << ambient.z << std::endl;
    //
    //
    //auto specular = Lighting::GetLightSpecular();
    //specular += 0.05f * (float)(!!InputManager::KeyHeld('z') - !!InputManager::KeyHeld('c'));
    //Lighting::SetLightSpecular(specular);
}

void Lighting::LightToggle()
{
    if (InputManager::KeyPressed('o'))
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

void Lighting::SetLightAmbient(const glm::vec3& ambient)
{
    light_.Ambient_ = ambient;
}

void Lighting::SetLightDiffuse(const glm::vec3& diffuse)
{
    light_.Diffuse_ = diffuse;
}

void Lighting::SetLightSpecular(const glm::vec3& specular)
{
    light_.Specular_ = specular;
}

void Lighting::SetLightPosition(const glm::vec3& new_pos)
{
    light_.Pos_ = new_pos;
}

void Lighting::SetLightViewPosition(const glm::vec3& view_pos)
{
    light_.View_ = view_pos;
}

void Lighting::SetLightColor(const glm::vec3& new_color)
{
    light_.Color_ = new_color;
}

const glm::vec3& Lighting::GetLightAmbient()
{
    return light_.Ambient_;
}

const glm::vec3& Lighting::GetLightDiffuse()
{
    return light_.Diffuse_;
}

const glm::vec3& Lighting::GetLightSpecular()
{
    return light_.Specular_;
}

const glm::vec3& Lighting::GetLightPosition()
{
    return light_.Pos_;
}

const glm::vec3& Lighting::GetLightViewPosition()
{
    return light_.View_;
}

const glm::vec3& Lighting::GetLightColor()
{
    return light_.Color_;
}

void Lighting::SetMaterialAmbient(const glm::vec3& ambient)
{
    material_.Ambient_ = ambient;
}

void Lighting::SetMaterialDiffuse(const glm::vec3& diffuse)
{
    material_.Diffuse_ = diffuse;
}

void Lighting::SetMaterialSpecular(const glm::vec3& specular)
{
    material_.Specular_ = specular;
}

void Lighting::SetMaterialShininess(float shininess)
{
    material_.Shininess_ = shininess;
}

const glm::vec3& Lighting::GetMaterialAmbient()
{
    return material_.Ambient_;
}

const glm::vec3& Lighting::GetMaterialDiffuse()
{
    return material_.Diffuse_;
}

const glm::vec3& Lighting::GetMaterialSpecular()
{
    return material_.Specular_;
}

const float Lighting::GetMaterialShininess()
{
    return material_.Shininess_;
}

