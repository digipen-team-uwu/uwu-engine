#pragma once
#include <unordered_map>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/BaseSystem.h>

using Point = glm::vec2;

class Picker : public BaseSystem<Picker>
{
public:

  struct AABB
  {
    AABB(float w_, float h_, Point bot_left) : w(w_), h(h_), bottom_left(bot_left) {}
    float w;
    float h;
    Point bottom_left;
  };

  enum class state
  {
    PICK,
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
  static bool IsPointInAABB(AABB aabb, Point p);
  static glm::mat3 GLFW_to_vp;
  static glm::mat3 ndc_to_vp;
  static glm::mat3 ndc_to_vf;
  static glm::vec3 mouse_world;
  static glm::vec3 ray_world;
  static EntityID saved_ID;
  static float saved_z;
  static std::unordered_map<EntityID, float> ID_and_depth;
};