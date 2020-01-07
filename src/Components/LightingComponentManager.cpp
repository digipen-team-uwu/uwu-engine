#include <UWUEngine/Component/LightingComponentManager.h>

template<> size_t RegisterComponentHelper<LightingComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<LightingComponentManager>(ComponentUpdateOrder::LAST);

EntityVector<LightType> LightingComponentManager::lightTypes{ goc::INITIAL_OBJECT_COUNT };
EntityVector<float> LightingComponentManager::shininess_{ goc::INITIAL_OBJECT_COUNT };
using Type = EntityManager::Type;

void LightingComponentManager::Update()
{
    
}

void LightingComponentManager::SetShininess(EntityID ID, const float shininess)
{
    shininess_[ID] = shininess;
}

float LightingComponentManager::GetShininess(EntityID ID)
{
    return shininess_[ID];
}

const std::vector<float>& LightingComponentManager::GetArrayShininess()
{
    return shininess_;
}

