#include <UWUEngine/Component/LightingComponentManager.h>

template<>
size_t RegisterComponentHelper<LightingComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<LightingComponentManager>(ComponentUpdateOrder::LAST);

//EntityVector<int> LightingComponentManager::lightState{ goc::INITIAL_OBJECT_COUNT };
EntityVector<LightType> LightingComponentManager::lightTypes{ goc::INITIAL_OBJECT_COUNT };
EntityVector<glm::vec3> LightingComponentManager::ambient_{ goc::INITIAL_OBJECT_COUNT };
EntityVector<glm::vec3> LightingComponentManager::diffuse_{ goc::INITIAL_OBJECT_COUNT };
EntityVector<glm::vec3> LightingComponentManager::specular_{ goc::INITIAL_OBJECT_COUNT };
EntityVector<float> LightingComponentManager::shininess_{ goc::INITIAL_OBJECT_COUNT };
using Type = EntityManager::Type;

LightingComponentManager::LightingComponentManager()
{
}

void LightingComponentManager::Update()
{
    
}

//void LightingComponentManager::SetLightState(EntityID ID, const int state)
//{
//    lightState[ID] = state;
//}

//void LightingComponentManager::SetLightState(EntityManager::Type type_, const int state)
//{
//    auto& ids = EntityManager::GetIDs();
//    for (auto i : ids)
//    {
//        auto type = EntityManager::GetType(i);
//        if (type == type_)
//        {
//            SetLightState(i, LC::LIGHT_STATE_ON);
//        }
//        else
//        {
//            SetLightState(i, LC::LIGHT_STATE_OFF);
//        }
//    }
//}

//void LightingComponentManager::SetLightStateAll()
//{
//    auto& ids = EntityManager::GetIDs();
//    for (auto i : ids)
//    {
//        SetLightState(i, LC::LIGHT_STATE_ON);
//    }
//}

//bool LightingComponentManager::GetLightState(EntityID ID)
//{
//    return lightState[ID];
//}
//
//const std::vector<int>& LightingComponentManager::GetArrayLightState()
//{
//    return lightState;
//}

void LightingComponentManager::SetAmbient(EntityID ID, const glm::vec3& ambient)
{
    ambient_[ID] = ambient;
}

void LightingComponentManager::SetDiffuse(EntityID ID, const glm::vec3& diffuse)
{
    diffuse_[ID] = diffuse;
}

void LightingComponentManager::SetSpecular(EntityID ID, const glm::vec3& specular)
{
    specular_[ID] = specular;
}

void LightingComponentManager::SetShininess(EntityID ID, const float shininess)
{
    shininess_[ID] = shininess;
}

const glm::vec3& LightingComponentManager::GetAmbient(EntityID ID)
{
    return ambient_[ID];
}

const glm::vec3& LightingComponentManager::GetDiffuse(EntityID ID)
{
    return diffuse_[ID];
}

const glm::vec3& LightingComponentManager::GetSpecular(EntityID ID)
{
    return specular_[ID];
}

float LightingComponentManager::GetShininess(EntityID ID)
{
    return shininess_[ID];
}

const std::vector<glm::vec3>& LightingComponentManager::GetArrayAmbient()
{
    return ambient_;
}

const std::vector<glm::vec3>& LightingComponentManager::GetArrayDiffuse()
{
    return diffuse_;
}

const std::vector<glm::vec3>& LightingComponentManager::GetArraySpecular()
{
    return specular_;
}

const std::vector<float>& LightingComponentManager::GetArrayShininess()
{
    return shininess_;
}

