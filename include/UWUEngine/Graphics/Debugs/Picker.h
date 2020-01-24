#pragma once
#include <unordered_map>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/BaseSystem.h>

class Picker : public BaseSystem<Picker>
{
public:
    Picker();
    ~Picker() = default;
    void Update() override;
    static void Pick();
    static void PickID();
    static glm::vec3 GetMouseWorld();
    static void CalculateMouseWorld(glm::vec2 Pos);
private:
  static glm::mat3 GLFW_to_vp;
  static glm::mat3 ndc_to_vp;
  static glm::mat3 ndc_to_vf;
  static glm::vec3 mouse_world;
  static EntityID saved_ID;
  static float saved_t;
  static std::unordered_map<EntityID, float> ID_to_time_;
};