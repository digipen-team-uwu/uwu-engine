/******************************************************************************/
/*!
\par        Project Umbra
\file       PointLight.cpp
\author     Chau Nguyen
\date       2019/11/20
\brief      Point Light

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Graphics/Lighting/PointLight.h>

//glm::vec3 LightSystem<LightType::PointLight>::position_;
//glm::vec3 LightSystem<LightType::PointLight>::ambient_;
//glm::vec3 LightSystem<LightType::PointLight>::diffuse_;
//glm::vec3 LightSystem<LightType::PointLight>::specular_;
//float LightSystem<LightType::PointLight>::constant_;
//float LightSystem<LightType::PointLight>::linear_;
//float LightSystem<LightType::PointLight>::quadratic_;

void LightSystem<LightType::PointLight>::Update()
{
    
}

void LightSystem<LightType::PointLight>::SetPosition(const glm::vec3& pos)
{
    position_ = pos;
}

void LightSystem<LightType::PointLight>::SetAmbient(const glm::vec3& ambient)
{
    ambient_ = ambient;
}

void LightSystem<LightType::PointLight>::SetDiffuse(const glm::vec3& diffuse)
{
    diffuse_ = diffuse;
}

void LightSystem<LightType::PointLight>::SetSpecular(const glm::vec3& specular)
{
    specular_ = specular;
}

void LightSystem<LightType::PointLight>::SetConstant(const float constant)
{
    constant_ = constant;
}

void LightSystem<LightType::PointLight>::SetLinear(const float linear)
{
    linear_ = linear;
}

void LightSystem<LightType::PointLight>::SetQuadratic(const float quadratic)
{
    quadratic_ = quadratic;
}

const glm::vec3& LightSystem<LightType::PointLight>::GetPosition() const
{
    return position_;
}

const glm::vec3& LightSystem<LightType::PointLight>::GetAmbient() const
{
    return ambient_;
}

const glm::vec3& LightSystem<LightType::PointLight>::GetDiffuse() const
{
    return diffuse_;
}

const glm::vec3& LightSystem<LightType::PointLight>::GetSpecular() const
{
    return specular_;
}

float LightSystem<LightType::PointLight>::GetConstant() const
{
    return constant_;
}

float LightSystem<LightType::PointLight>::GetLinear() const
{
    return linear_;
}

float LightSystem<LightType::PointLight>::GetQuadratic() const
{
    return quadratic_;
}

