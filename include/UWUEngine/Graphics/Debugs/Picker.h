#pragma once
#include <unordered_map>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/BaseSystem.h>

class Picker : public BaseSystem<Picker>
{
public:

  enum class state
  {
    PICKED,
    RELEASE,

    Total
  };

  Picker();
  ~Picker() = default;
  void Update() override;
  static void Pick();
  static void PickID();
  static glm::vec2 GetMouseWorld();
  static void CalculateMouseWorld(glm::vec2 Pos);
  static void Attaching(EntityID ID);
  static void Detaching();
private:
  static void Reset();
  static glm::mat3 GLFW_to_vp;
  static glm::mat3 ndc_to_vp;
  static glm::mat3 ndc_to_vf;
  static glm::vec3 mouse_world;
  static EntityID saved_ID;
  static float saved_d;
  static std::unordered_map<EntityID, std::pair<float,glm::vec2>> ID_and_distance;
  static bool switch_;
  static state state_;
};