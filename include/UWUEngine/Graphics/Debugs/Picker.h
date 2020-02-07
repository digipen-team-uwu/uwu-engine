#pragma once
#include <unordered_map>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/BaseSystem.h>

class Picker : public BaseSystem<Picker>
{
public:
  struct PickerData;
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
  static glm::vec2 GetMouseWorld();
  static void CalculateMouseWorld(glm::vec2 Pos);
private:
  struct PickerData
  {
    EntityID ID;
    glm::vec2 baryPosition;
    glm::vec2 uv;
  };
  static bool CheckPixelData(float distance);
  static void DragObject(EntityID chosen_ID);
  static void Reset();
  static void PickID();
  static glm::mat3 GLFW_to_vp;
  static glm::mat3 ndc_to_vp;
  static glm::mat3 ndc_to_vf;
  static glm::vec3 mouse_world;
  static EntityID saved_ID;
  static float saved_d;
  static std::map<float, PickerData> Data_;
  static bool switch_;
  static state state_;
};