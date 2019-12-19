/******************************************************************************/
/*!
\par        Project Umbra
\file       DirectionalLight.cpp
\author     Chau Nguyen
\date       2019/11/20
\brief      Directional Light

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Graphics/Lighting/DirectionalLight.h>

//glm::vec3 LightSystem<LightType::DirectionalLight>::direction_;
//glm::vec3 LightSystem<LightType::DirectionalLight>::ambient_;
//glm::vec3 LightSystem<LightType::DirectionalLight>::diffuse_;
//glm::vec3 LightSystem<LightType::DirectionalLight>::specular_;

LightSystem<LightType::DirectionalLight>::LightSystem()
{
    
}

void LightSystem<LightType::DirectionalLight>::Update()
{
    
}


void LightSystem<LightType::DirectionalLight>::SetDirection(const glm::vec3& dir)
{
    direction_ = dir;
}

void LightSystem<LightType::DirectionalLight>::SetAmbient(const glm::vec3& ambient)
{
    ambient_ = ambient;
}

void LightSystem<LightType::DirectionalLight>::SetDiffuse(const glm::vec3& diffuse)
{
    diffuse_ = diffuse;
}

void LightSystem<LightType::DirectionalLight>::SetSpecular(const glm::vec3& specular)
{
    specular_ = specular;
}

const glm::vec3& LightSystem<LightType::DirectionalLight>::GetDirection() const
{
    return direction_;
}

const glm::vec3& LightSystem<LightType::DirectionalLight>::GetAmbient() const
{
    return ambient_;
}

const glm::vec3& LightSystem<LightType::DirectionalLight>::GetDiffuse() const
{
    return diffuse_;
}

const glm::vec3& LightSystem<LightType::DirectionalLight>::GetSpecular() const
{
    return specular_;
}