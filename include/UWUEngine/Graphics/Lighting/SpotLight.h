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
#include <UWUEngine/Graphics/Lighting/Lighting.h>

template<>
class LightSystem<LightType::SpotLight> : public LightBase
{
public:
    LightSystem();
    ~LightSystem() = default;
    void Update() override;

    static void SetPosition(EntityID ID, const glm::vec3& pos);
    static void SetDirection(EntityID ID, const glm::vec3& dir);

    static void SetAmbient(EntityID ID, const glm::vec3& ambient);
    static void SetDiffuse(EntityID ID, const glm::vec3& diffuse);
    static void SetSpecular(EntityID ID, const glm::vec3& specular);

    static void SetConstant(EntityID ID, float constant);
    static void SetLinear(EntityID ID, float linear);
    static void SetQuadratic(EntityID ID, float quadratic);

    static void SetCutOff(EntityID ID, float cutoff);
    static void SetOuterCutOff(EntityID ID, float outer_cutoff);

    static const glm::vec3& GetPosition(EntityID ID);
    static const glm::vec3& GetDirection(EntityID ID);

    static const glm::vec3& GetAmbient(EntityID ID);
    static const glm::vec3& GetDiffuse(EntityID ID);
    static const glm::vec3& GetSpecular(EntityID ID);

    static float GetConstant(EntityID ID);
    static float GetLinear(EntityID ID);
    static float GetQuadratic(EntityID ID);

    static float GetCutOff(EntityID ID);
    static float GetOuterCutOff(EntityID ID);

    static std::vector<glm::vec3>& GetArrayPosition();
    static std::vector<glm::vec3>& GetArrayDirection();

    static std::vector<glm::vec3>& GetArrayAmbient();
    static std::vector<glm::vec3>& GetArrayDiffuse();
    static std::vector<glm::vec3>& GetArraySpecular();

    static std::vector<float>& GetArrayConstant();
    static std::vector<float>& GetArrayLinear();
    static std::vector<float>& GetArrayQuadratic();

    static std::vector<float>& GetArrayCutOff();
    static std::vector<float>& GetArrayOuterCutOff();

private:
    static EntityVector<glm::vec3> position_;
    static EntityVector<glm::vec3> direction_;
    
    static EntityVector<glm::vec3> ambient_;
    static EntityVector<glm::vec3> diffuse_;
    static EntityVector<glm::vec3> specular_;
    
    static EntityVector<float> constant_;
    static EntityVector<float> linear_;
    static EntityVector<float> quadratic_;
    
    static EntityVector<float> cutOff_;
    static EntityVector<float> outerCutOff_;
};