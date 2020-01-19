/******************************************************************************/
/*!
\par        Project Umbra
\file       SpotLight.cpp
\author     Chau Nguyen
\date       2019/11/20
\brief      Spot Light

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Graphics/Lighting/SpotLight.h>

EntityVector<glm::vec3> LightSystem<LightType::SpotLight>::position_;
EntityVector<glm::vec3> LightSystem<LightType::SpotLight>::direction_;
EntityVector<glm::vec3> LightSystem<LightType::SpotLight>::ambient_;
EntityVector<glm::vec3> LightSystem<LightType::SpotLight>::diffuse_;
EntityVector<glm::vec3> LightSystem<LightType::SpotLight>::specular_;
EntityVector<float>LightSystem<LightType::SpotLight>::constant_;
EntityVector<float>LightSystem<LightType::SpotLight>::linear_;
EntityVector<float>LightSystem<LightType::SpotLight>::quadratic_;
EntityVector<float>LightSystem<LightType::SpotLight>::cutOff_;
EntityVector<float>LightSystem<LightType::SpotLight>::outerCutOff_;

LightSystem<LightType::SpotLight>::LightSystem()
{
    
}

void LightSystem<LightType::SpotLight>::Update()
{
    
}

void LightSystem<LightType::SpotLight>::SetPosition(EntityID ID, const glm::vec3& pos)
{
    position_[ID] = pos;
}

void LightSystem<LightType::SpotLight>::SetDirection(EntityID ID, const glm::vec3& dir)
{
    direction_[ID] = dir;
}

void LightSystem<LightType::SpotLight>::SetAmbient(EntityID ID, const glm::vec3& ambient)
{
    ambient_[ID] = ambient;
}

void LightSystem<LightType::SpotLight>::SetDiffuse(EntityID ID, const glm::vec3& diffuse)
{
    diffuse_[ID] = diffuse;
}

void LightSystem<LightType::SpotLight>::SetSpecular(EntityID ID, const glm::vec3& specular)
{
    specular_[ID] = specular;
}

void LightSystem<LightType::SpotLight>::SetConstant(EntityID ID, const float constant)
{
    constant_[ID] = constant;
}

void LightSystem<LightType::SpotLight>::SetLinear(EntityID ID, const float linear)
{
    linear_[ID] = linear;
}

void LightSystem<LightType::SpotLight>::SetQuadratic(EntityID ID, const float quadratic)
{
    quadratic_[ID] = quadratic;
}

void LightSystem<LightType::SpotLight>::SetCutOff(EntityID ID, float cutoff)
{
    cutOff_[ID] = cutoff;
}

void LightSystem<LightType::SpotLight>::SetOuterCutOff(EntityID ID, float outer_cutoff)
{
    outerCutOff_[ID] = outer_cutoff;
}

const glm::vec3& LightSystem<LightType::SpotLight>::GetPosition(EntityID ID)
{
    return position_[ID];
}

const glm::vec3& LightSystem<LightType::SpotLight>::GetDirection(EntityID ID)
{
    return direction_[ID];
}

const glm::vec3& LightSystem<LightType::SpotLight>::GetAmbient(EntityID ID)
{
    return ambient_[ID];
}

const glm::vec3& LightSystem<LightType::SpotLight>::GetDiffuse(EntityID ID)
{
    return diffuse_[ID];
}

const glm::vec3& LightSystem<LightType::SpotLight>::GetSpecular(EntityID ID)
{
    return specular_[ID];
}

float LightSystem<LightType::SpotLight>::GetConstant(EntityID ID)
{
    return constant_[ID];
}

float LightSystem<LightType::SpotLight>::GetLinear(EntityID ID)
{
    return linear_[ID];
}

float LightSystem<LightType::SpotLight>::GetQuadratic(EntityID ID)
{
    return quadratic_[ID];
}

float LightSystem<LightType::SpotLight>::GetCutOff(EntityID ID)
{
    return cutOff_[ID];
}

float LightSystem<LightType::SpotLight>::GetOuterCutOff(EntityID ID)
{
    return outerCutOff_[ID];
}

std::vector<glm::vec3>& LightSystem<LightType::SpotLight>::GetArrayPosition()
{
    return position_;
}

std::vector<glm::vec3>& LightSystem<LightType::SpotLight>::GetArrayDirection()
{
    return direction_;
}

std::vector<glm::vec3>& LightSystem<LightType::SpotLight>::GetArrayAmbient()
{
    return ambient_;
}

std::vector<glm::vec3>& LightSystem<LightType::SpotLight>::GetArrayDiffuse()
{
    return diffuse_;
}

std::vector<glm::vec3>& LightSystem<LightType::SpotLight>::GetArraySpecular()
{
    return specular_;
}

std::vector<float>& LightSystem<LightType::SpotLight>::GetArrayConstant()
{
    return constant_;
}

std::vector<float>& LightSystem<LightType::SpotLight>::GetArrayLinear()
{
    return linear_;
}

std::vector<float>& LightSystem<LightType::SpotLight>::GetArrayQuadratic()
{
    return quadratic_;
}

std::vector<float>& LightSystem<LightType::SpotLight>::GetArrayCutOff()
{
    return cutOff_;
}

std::vector<float>& LightSystem<LightType::SpotLight>::GetArrayOuterCutOff()
{
    return outerCutOff_;
}
