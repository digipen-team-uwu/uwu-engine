#pragma once
#include "BaseComponent.h"
#include <UWUEngine/constants.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>

namespace LC = LightingConstant;

class LightingComponentManager : public BaseComponent<LightingComponentManager>
{
public:
    LightingComponentManager() = default;
    ~LightingComponentManager() = default;
    void Update() override;
    void InitObject(EntityID ID) override {};
    void ShutdownObject(EntityID ID) override {};

    // Material
    static void SetShininess(EntityID ID, const float shininess);
    static float GetShininess(EntityID ID);
    static const std::vector<float>& GetArrayShininess();

private:

    // TODO: instancing those vectors below in the future
    static EntityVector<LightType> lightTypes;

    // Material
    static EntityVector<float> shininess_;
};