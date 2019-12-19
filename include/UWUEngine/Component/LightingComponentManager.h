#pragma once
#include <UWUEngine/Component/BaseComponent.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>

namespace LC = LightingConstant;

class LightingComponentManager : public BaseComponent<LightingComponentManager>
{
public:
    LightingComponentManager();
    ~LightingComponentManager() = default;
    void Update() override;
    void InitObject(EntityID ID) override {};
    void ShutdownObject(EntityID ID) override {};

    //static void SetLightState(EntityID, const int);
    //static void SetLightState(EntityManager::Type, const int);
    //static void SetLightStateAll();
    //static bool GetLightState(EntityID);
    //static const std::vector<int>& GetArrayLightState();

    // Material
    static void SetAmbient(EntityID ID, const glm::vec3& ambient);
    static void SetDiffuse(EntityID ID, const glm::vec3& diffuse);
    static void SetSpecular(EntityID ID, const glm::vec3& specular);
    static void SetShininess(EntityID ID, const float shininess);

    static const glm::vec3& GetAmbient(EntityID ID);
    static const glm::vec3& GetDiffuse(EntityID ID);
    static const glm::vec3& GetSpecular(EntityID ID);
    static float GetShininess(EntityID ID);

    static const std::vector<glm::vec3>& GetArrayAmbient();
    static const std::vector<glm::vec3>& GetArrayDiffuse();
    static const std::vector<glm::vec3>& GetArraySpecular();
    static const std::vector<float>& GetArrayShininess();

private:

    // TODO: instancing those vectors below in the future
    static EntityVector<LightType> lightTypes;

    // Material
    static EntityVector<glm::vec3> ambient_;
    static EntityVector<glm::vec3> diffuse_;
    static EntityVector<glm::vec3> specular_;
    static EntityVector<float> shininess_;
};
